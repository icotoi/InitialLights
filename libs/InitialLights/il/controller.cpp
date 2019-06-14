#include "controller.h"
#include "pwmlight.h"
#include "rgblight.h"
#include "analogiclight.h"

//#include <QRandomGenerator>
//#include <QTimer>

#if defined (Q_OS_MAC)
#include <QBluetoothUuid>
#else
#include <QBluetoothAddress>
#endif

namespace il {

namespace  {
const QBluetoothUuid uuidService(QStringLiteral("6E400001-B5A3-F393-E0A9-E50E24DCCA9E"));
const QBluetoothUuid writeCharacteristicUuid(QStringLiteral("6E400002-B5A3-F393-E0A9-E50E24DCCA9E"));
const QBluetoothUuid readCharacteristicUuid(QStringLiteral("6E400003-B5A3-F393-E0A9-E50E24DCCA9E"));
}

Controller::Controller(QObject *parent)
    : ControllerBase (parent)
{
}

Controller::Controller(const QBluetoothDeviceInfo &info, QObject *parent)
    : ControllerBase (parent)
    , m_info { info }
{
    update_name(m_info.name());
    update_address(safeAddress(m_info));
}

Controller::~Controller()
{
    clear();
}

void Controller::clear()
{
    ControllerBase::clear();

    m_hasReceivedInitialState = false;

    m_notificationDescriptor = QLowEnergyDescriptor();

    m_service.reset();

    if (!m_controller.isNull()) {
        m_controller->disconnectFromDevice();
        m_controller.reset();
    }

    update_isBusy(false);

    qDebug() << "light controller internal state cleared";
}

void Controller::read(const QJsonObject &json)
{
    ControllerBase::read(json);
#if defined(Q_OS_MAC)
    m_info = QBluetoothDeviceInfo(QBluetoothUuid(address()), name(), 0);
#else
    m_info = QBluetoothDeviceInfo(QBluetoothAddress(address()), name(), 0);
#endif
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

        writeToDevice("U?\n");

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

    qDebug() << "received response: " << data;

    updateFromDevice(data.simplified());
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
                clearLights();

                auto controllerType = data.right(2).toInt();
                switch (controllerType) {
                case 2:
                    // 2 x Analogic
                    update_controllerType(V1_2x10V);
                    for (int i = 0; i < 2; ++i) {
                        auto light = new AnalogicLight(QString::number(i+1), this);
                        get_analogicLights()->append(light);
                        light->set_value(data.mid(1 + i*2, 2).toInt(nullptr, 16));
                        connect(light, &AnalogicLight::valueChanged, this, &Controller::updateDevice);
                    }
                    break;
                case 3:
                    // 4 x PWM
                    update_controllerType(V1_4xPWM);
                    for (int i = 0; i < 4; ++i) {
                        auto light = new PWMLight(QString::number(i+1), this);
                        get_pwmLights()->append(light);
                        light->set_value(data.mid(1 + i*2, 2).toInt(nullptr, 16));
                        connect(light, &PWMLight::valueChanged, this, &Controller::updateDevice);
                    }
                    break;
                default:
                    // 1 x PWM + 1 x RGB
                    update_controllerType(V1_1xPWM_1xRGB);
                    auto pwmLight = new PWMLight("1", this);
                    get_pwmLights()->append(pwmLight);
                    pwmLight->set_value(data.mid(1, 2).toInt(nullptr, 16));
                    connect(pwmLight, &PWMLight::valueChanged, this, &Controller::updateDevice);

                    auto rgbLight = new RGBLight("2", this);
                    get_rgbLights()->append(rgbLight);
                    rgbLight->set_redValue(data.mid(3, 2).toInt(nullptr, 16));
                    rgbLight->set_greenValue(data.mid(5, 2).toInt(nullptr, 16));
                    rgbLight->set_blueValue(data.mid(7, 2).toInt(nullptr, 16));
                    connect(rgbLight, &RGBLight::redValueChanged, this, &Controller::updateDevice);
                    connect(rgbLight, &RGBLight::greenValueChanged, this, &Controller::updateDevice);
                    connect(rgbLight, &RGBLight::blueValueChanged, this, &Controller::updateDevice);
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

bool Controller::writeToDevice(const QByteArray &data)
{
    auto writeCharacteristic = m_service->characteristic(writeCharacteristicUuid);
    if (!writeCharacteristic.isValid()) {
        update_message("Cannot get write characteristic");
        qDebug() << "cannot get write characteristic";
        return false;
    }

    m_command = data;
    m_service->writeCharacteristic(writeCharacteristic, m_command,  QLowEnergyService::WriteMode::WriteWithoutResponse);

    return true;
}

} // namespace il
