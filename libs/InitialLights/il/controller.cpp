#include "controller.h"
#include "light.h"

#include "jsonhelpers.h"

#if defined (Q_OS_MAC)
#include <QBluetoothUuid>
#else
#include <QBluetoothAddress>
#endif

#include <QEventLoop>
#include <QJsonArray>
#include <QJsonObject>
#include <QMetaEnum>

namespace il {

namespace  {
const QString jsonNameTag { "name" };
const QString jsonAddressTag { "address" };
const QString jsonControllerTypeTag { "type" };
const QString jsonLightsTag { "lights" };

const QBluetoothUuid uuidService(QStringLiteral("6E400001-B5A3-F393-E0A9-E50E24DCCA9E"));
const QBluetoothUuid writeCharacteristicUuid(QStringLiteral("6E400002-B5A3-F393-E0A9-E50E24DCCA9E"));
const QBluetoothUuid readCharacteristicUuid(QStringLiteral("6E400003-B5A3-F393-E0A9-E50E24DCCA9E"));
}

Controller::Controller(QObject *parent)
    : QObject(parent)
    , m_controllerType { UndefinedControllerType }
    , m_isBusy { false }
    , m_isConnected { false }
    , m_lights { new QQmlObjectListModel<Light>(this) }
{
}

Controller::Controller(const QBluetoothDeviceInfo &info, QObject *parent)
    : Controller(parent)
{
    m_info = info;
    update_name(m_info.name());
    update_address(safeAddress(m_info));
}

Controller::~Controller()
{
    clear();
}

QByteArray Controller::updateDeviceCommand() const
{
    QString command;

    switch (controllerType()) {
    case V1_2x10V:
    {
        Q_ASSERT(m_lights->size() == 2);
        Q_ASSERT(m_lights->at(0)->lightType() == Light::Analogic);
        Q_ASSERT(m_lights->at(1)->lightType() == Light::Analogic);

        command = QStringLiteral(u"US%1%2%3\n")
                .arg(m_lights->at(0)->value(), 2, 16, QChar('0'))
                .arg(m_lights->at(1)->value(), 2, 16, QChar('0'))
                .arg(2, 6, 16, QChar('0'))
                ;
        break;
    }
    case V1_4xPWM: {
        Q_ASSERT(m_lights->size() == 4);
        Q_ASSERT(m_lights->at(0)->lightType() == Light::PWM);
        Q_ASSERT(m_lights->at(1)->lightType() == Light::PWM);
        Q_ASSERT(m_lights->at(2)->lightType() == Light::PWM);
        Q_ASSERT(m_lights->at(3)->lightType() == Light::PWM);

        command = QString("US%1%2%3%4%5\n")
                .arg(m_lights->at(0)->value(), 2, 16, QChar('0'))
                .arg(m_lights->at(1)->value(), 2, 16, QChar('0'))
                .arg(m_lights->at(2)->value(), 2, 16, QChar('0'))
                .arg(m_lights->at(3)->value(), 2, 16, QChar('0'))
                .arg(3, 2, 16, QChar('0'));
        break;
    }
    case V1_1xPWM_1xRGB: {
        Q_ASSERT(m_lights->size() == 2);
        Q_ASSERT(m_lights->at(0)->lightType() == Light::PWM);
        Q_ASSERT(m_lights->at(1)->lightType() == Light::RGB);

        auto pwmLight = m_lights->at(0);
        auto rgbLight = m_lights->at(1);
        command = QString("US%1%2%3%4%5\n")
                .arg(pwmLight->value(), 2, 16, QChar('0'))
                .arg(rgbLight->redValue(), 2, 16, QChar('0'))
                .arg(rgbLight->greenValue(), 2, 16, QChar('0'))
                .arg(rgbLight->blueValue(), 2, 16, QChar('0'))
                .arg(1, 2, 16, QChar('0'));
        break;
    }
    default:
        qWarning() << "don't know how to save controller state for controller type:" << controllerType();
        break;
    }

    return command.toUpper().toUtf8();
}

void Controller::clear()
{
    if (m_needsInitialState) {
        m_lights->clear();
    }

    m_hasReceivedInitialState = false;

    m_notificationDescriptor = QLowEnergyDescriptor();

    m_service.reset();

    if (!m_controller.isNull()) {
        m_controller->disconnectFromDevice();
        m_controller.reset();
    }

    update_isBusy(false);
    update_isConnected(false);
}

void Controller::read(const QJsonObject &json)
{
    safeRead(json, jsonNameTag, QJsonValue::String, [&](const QJsonValue& json) { update_name(json.toString()); });
    safeRead(json, jsonAddressTag, QJsonValue::String, [&](const QJsonValue& json) { update_address(json.toString()); });
    safeRead(json, jsonControllerTypeTag, QJsonValue::String, [&](const QJsonValue& json) {
        int value = QMetaEnum::fromType<ControllerType>().keyToValue(json.toString().toStdString().c_str());
        if (value >= 0) {
            ControllerType ct { ControllerType(value) };
            update_controllerType(ct);
        }
    });

    readModel(json, jsonLightsTag, m_lights);

#if defined(Q_OS_MAC)
    m_info = QBluetoothDeviceInfo(QBluetoothUuid(address()), name(), 0);
#else
    m_info = QBluetoothDeviceInfo(QBluetoothAddress(address()), name(), 0);
#endif
}

void Controller::write(QJsonObject &json) const
{
    json[jsonNameTag] = m_name;
    json[jsonAddressTag] = m_address;
    json[jsonControllerTypeTag] = QMetaEnum::fromType<ControllerType>().valueToKey(m_controllerType);

    writeModel(json, jsonLightsTag, m_lights);
}

QString Controller::safeAddress(const QBluetoothDeviceInfo &info)
{
#if defined(Q_OS_MAC)
    // workaround for Core Bluetooth:
    return info.deviceUuid().toString();
#else
    return info.address().toString();
#endif
}

bool Controller::isValidDevice(const QBluetoothDeviceInfo &info)
{
    return info.serviceUuids().contains(uuidService);
}

void Controller::blink(Light *light, int offset)
{
    // FIXME: demo requires negative offset
//    if (offset < 0) {
//        qWarning() << "offset blink must be positive; received:" << offset;
//        return;
//    }

    if (!light) {
        qWarning() << "trying to blink NULL light";
        return;
    }

    int index = m_lights->indexOf(light);
    if (index < 0) {
        qWarning() << "light" << light->name() << "not in controller" << m_name;
        return;
    }

    index += offset;

    if (index > 3) {
        qWarning() << "don't know how to blink channel" << index;
    }

    writeToDevice("UB" + QByteArray::number(index) + "\n");
}

void Controller::connectToController()
{
    // just for safety
    clear();

    update_isBusy(true);

    m_controller.reset(new QLowEnergyController(m_info, this));

    connect(m_controller.get(), &QLowEnergyController::serviceDiscovered,
            this, &Controller::serviceDiscovered);
    connect(m_controller.get(), &QLowEnergyController::discoveryFinished,
            this, &Controller::serviceScanDone);
    connect(m_controller.get(), qOverload<QLowEnergyController::Error>(&QLowEnergyController::error),
            this, &Controller::controllerError);
    connect(m_controller.get(), &QLowEnergyController::connected,
            this, &Controller::controllerConnected);
    connect(m_controller.get(), &QLowEnergyController::disconnected,
            this, &Controller::controllerDisconnected);

    m_controller->connectToDevice();
}

void Controller::disconnectFromController()
{
    //disable notifications before disconnecting
    if (m_notificationDescriptor.isValid()
            && m_service
            && m_notificationDescriptor.value() == QByteArray::fromHex("0100")) {
        m_service->writeDescriptor(m_notificationDescriptor, QByteArray::fromHex("0000"));
    } else {
        clear();
    }
}

void Controller::serviceDiscovered(const QBluetoothUuid & uuid)
{
    if (uuid == uuidService) {
        if (m_service.isNull()) {
            update_message("Service found");
            qDebug() << "service found";
            m_service.reset(m_controller->createServiceObject(uuid, this));
        } else {
            qWarning() << "service already found";
        }
    }
}

void Controller::serviceScanDone()
{
    qDebug() <<  "service scan done";

    if (!m_service.isNull()) {
        connect(m_service.get(), &QLowEnergyService::stateChanged,
                this, &Controller::serviceStateChanged);
        connect(m_service.get(), &QLowEnergyService::characteristicChanged,
                this, &Controller::serviceCharacteristicChanged);
        connect(m_service.get(), &QLowEnergyService::descriptorWritten,
                this, &Controller::serviceDescriptorWritten);
        connect(m_service.get(), qOverload<QLowEnergyService::ServiceError>(&QLowEnergyService::error),
                this, &Controller::serviceError);
        m_service->discoverDetails();
        update_message("Connecting to service");
        qDebug() << "connecting to service...";
    } else {
        update_message("No service found");
        update_isBusy(false);
        qDebug() << "no service found";
    }
}

void Controller::controllerError(QLowEnergyController::Error error)
{
    update_message("Cannot connect to controller");
    qWarning() << "Controller Error:" << error;
}

void Controller::controllerConnected()
{
    qDebug() << "connected to controller; discovering services...";
    m_controller->discoverServices();
}

void Controller::controllerDisconnected()
{
    update_message("Controller disconnected");
    qWarning() << "controller disconnected";
}

void Controller::serviceStateChanged(QLowEnergyService::ServiceState state)
{
    qDebug() << "service state changed" << state;

    switch (state) {
    case QLowEnergyService::ServiceDiscovered: {
        const QLowEnergyCharacteristic readCharacteristic = m_service->characteristic(readCharacteristicUuid);
        if (!readCharacteristic.isValid()) {
            update_message("Cannot get read characteristic");
            qDebug() << "cannot get read characteristic";
            break;
        }

        m_notificationDescriptor = readCharacteristic.descriptor(QBluetoothUuid::ClientCharacteristicConfiguration);
        if (!m_notificationDescriptor.isValid()) {
            update_message("Cannot set notification descriptor");
            qWarning() << "cannot set notification descriptor";
            break;
        }

        m_service->writeDescriptor(m_notificationDescriptor, QByteArray::fromHex("0100"));
        update_message("Connected");
        qDebug() << "connected";

        update_isConnected(true);

        if (m_needsInitialState) {
            writeToDevice("U?\n");
        } else {
            update_isBusy(false);
        }

        break;
    }
    default:
        //nothing for now
        break;
    }
}

void Controller::serviceCharacteristicChanged(const QLowEnergyCharacteristic &characteristic, const QByteArray &data)
{
    // ignore any other characteristic change -> shouldn't really happen though
    if (characteristic.uuid() != QBluetoothUuid(readCharacteristicUuid))
        return;

    const char messageSeparator { '\n' };

    int index = data.indexOf(messageSeparator);
    if (m_readBuffer.size() > 0 || index < 0) {
        qDebug() << "received partial data:" << data;
    }

    if (index >=0) {
        index += m_readBuffer.size();
    }

    m_readBuffer += data;

    if (index >= 0) {
        auto response = m_readBuffer.left(index + 1);
        m_readBuffer = m_readBuffer.mid(index + 2);
        qDebug() << "received response: " << response << "(left in read buffer:" << m_readBuffer <<")";
        updateFromDevice(response.simplified());
    }
}

void Controller::serviceDescriptorWritten(const QLowEnergyDescriptor &descriptor, const QByteArray &data)
{
    if (descriptor.isValid()
            && descriptor == m_notificationDescriptor
            && data == QByteArray::fromHex("0000")) {
        // disabled notifications -> assume disconnect intent
        clear();
    }
}

void Controller::serviceError(QLowEnergyService::ServiceError e)
{
    switch (e) {
    case QLowEnergyService::DescriptorWriteError:
        update_message("Cannot obtain service notifications");
        qWarning() << "cannot obtain service notifications";
        break;
    default:
        qWarning() << "service error:" << e;
    }
}

void Controller::updateFromDevice(const QByteArray &data)
{
    if (data.length() != 11) {
        update_message("Received invalid data");
        qWarning() << "received invalid data received from controller: 11 !=" << data.length() << "data:" << data;
    } else {
        if(data.startsWith("*")) {
            if(m_command.startsWith("U?")) {
                m_hasReceivedInitialState = true;
                get_lights()->clear();

                auto controllerType = data.right(2).toInt();
                switch (controllerType) {
                case 2:
                    // 2 x Analogic
                    update_controllerType(V1_2x10V);
                    for (int i = 0; i < 2; ++i) {
                        auto light = new Light(Light::Analogic, QString::number(i+1), this);
                        get_lights()->append(light);
                        light->set_value(data.mid(1 + i*2, 2).toInt(nullptr, 16));
                        connect(light, &Light::valueChanged, this, &Controller::updateDevice);
                    }
                    break;
                case 3:
                    // 4 x PWM
                    update_controllerType(V1_4xPWM);
                    for (int i = 0; i < 4; ++i) {
                        auto light = new Light(Light::PWM, QString::number(i+1), this);
                        get_lights()->append(light);
                        light->set_value(data.mid(1 + i*2, 2).toInt(nullptr, 16));
                        connect(light, &Light::valueChanged, this, &Controller::updateDevice);
                    }
                    break;
                default:
                    // 1 x PWM + 1 x RGB
                    update_controllerType(V1_1xPWM_1xRGB);
                    auto pwmLight = new Light(Light::PWM, "1", this);
                    get_lights()->append(pwmLight);
                    pwmLight->set_value(data.mid(1, 2).toInt(nullptr, 16));
                    connect(pwmLight, &Light::valueChanged, this, &Controller::updateDevice);

                    auto rgbLight = new Light(Light::RGB, "2", this);
                    get_lights()->append(rgbLight);
                    rgbLight->set_redValue(data.mid(3, 2).toInt(nullptr, 16));
                    rgbLight->set_greenValue(data.mid(5, 2).toInt(nullptr, 16));
                    rgbLight->set_blueValue(data.mid(7, 2).toInt(nullptr, 16));
                    connect(rgbLight, &Light::redValueChanged, this, &Controller::updateDevice);
                    connect(rgbLight, &Light::greenValueChanged, this, &Controller::updateDevice);
                    connect(rgbLight, &Light::blueValueChanged, this, &Controller::updateDevice);
                    break;
                }
            } else if(m_command.startsWith("UV")) {
                // TODO: implement read scene response parser
            } else if(m_command.startsWith("UI")) {
                // TODO: implement invoke scene response parser
            }
        }
    }

    update_isBusy(false);
}

void Controller::updateDevice()
{
    QByteArray command = updateDeviceCommand();

    if(command.length() != 13) {
        qCritical() << "ERROR: invalid command length: 13 !=" << command.length() << "command:" << command;
        return;
    }

    if (m_command != command) {
        qDebug() << "sending update to device:" << command;
        writeToDevice(command);
    }
}

bool Controller::writeToDevice(const QByteArray &data, bool clearReadBuffer)
{
    if (!connectIfNeeded()) {
        return false;
    }

    if (clearReadBuffer) {
        m_readBuffer.clear();
    }

    auto writeCharacteristic = m_service->characteristic(writeCharacteristicUuid);
    if (!writeCharacteristic.isValid()) {
        update_message("Cannot get write characteristic");
        qDebug() << "cannot get write characteristic";
        return false;
    }

    m_command = data;

    qDebug() << "sending command to device:" << m_command;

    m_service->writeCharacteristic(writeCharacteristic, m_command,  QLowEnergyService::WriteMode::WriteWithoutResponse);

    return true;
}

bool Controller::connectIfNeeded()
{
    if (m_isConnected)
        return true;

    m_needsInitialState = false;

    QEventLoop localEventLoop;
    connect(this, &Controller::isConnectedChanged, [&localEventLoop, this](){
        if (m_isConnected) {
            localEventLoop.quit();
        }
    });

    qDebug() << "reconnecting controller";

    connectToController();

    qDebug() << "waiting...";

    localEventLoop.exec();

    qDebug() << "done";

    m_needsInitialState = true;

    return true;
}
} // namespace il
