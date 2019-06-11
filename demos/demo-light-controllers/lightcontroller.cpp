#include "lightcontroller.h"
#include "lightcontrollerpwmchannel.h"
#include "lightcontrollerrgbchannel.h"
#include "lightcontrollervoltagechannel.h"

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

LightController::LightController(const QBluetoothDeviceInfo &info, QObject *parent)
    : AbstractLightController (parent)
    , m_info { info }
{
    update_name(m_info.name());
    update_address(address(m_info));
}

LightController::~LightController()
{
    clear();
}

void LightController::clear()
{
    AbstractLightController::clear();

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

QString LightController::address(const QBluetoothDeviceInfo &info)
{
#if defined(Q_OS_MAC)
    // workaround for Core Bluetooth:
    return info.deviceUuid().toString();
#else
    return info.address().toString();
#endif
}

bool LightController::isValidDevice(const QBluetoothDeviceInfo &info)
{
    return info.serviceUuids().contains(uuidService);
}

void LightController::connectToController()
{
    // just for safety
    clear();

    update_isBusy(true);

    m_controller.reset(new QLowEnergyController(m_info, this));

    connect(m_controller.get(), &QLowEnergyController::serviceDiscovered,
            this, &LightController::serviceDiscovered);
    connect(m_controller.get(), &QLowEnergyController::discoveryFinished,
            this, &LightController::serviceScanDone);
    connect(m_controller.get(), qOverload<QLowEnergyController::Error>(&QLowEnergyController::error),
            this, &LightController::controllerError);
    connect(m_controller.get(), &QLowEnergyController::connected,
            this, &LightController::controllerConnected);
    connect(m_controller.get(), &QLowEnergyController::disconnected,
            this, &LightController::controllerDisconnected);

    m_controller->connectToDevice();
}

void LightController::disconnectFromController()
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

void LightController::serviceDiscovered(const QBluetoothUuid & uuid)
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

void LightController::serviceScanDone()
{
    qDebug() <<  "service scan done";

    if (!m_service.isNull()) {
        connect(m_service.get(), &QLowEnergyService::stateChanged,
                this, &LightController::serviceStateChanged);
        connect(m_service.get(), &QLowEnergyService::characteristicChanged,
                this, &LightController::serviceCharacteristicChanged);
        connect(m_service.get(), &QLowEnergyService::descriptorWritten,
                this, &LightController::serviceDescriptorWritten);
        connect(m_service.get(), qOverload<QLowEnergyService::ServiceError>(&QLowEnergyService::error),
                this, &LightController::serviceError);
        m_service->discoverDetails();
        update_message("Connecting to service");
        qDebug() << "connecting to service...";
    } else {
        update_message("No service found");
        update_isBusy(false);
        qDebug() << "no service found";
    }
}

void LightController::controllerError(QLowEnergyController::Error error)
{
    update_message("Cannot connect to controller");
    qWarning() << "Controller Error:" << error;
}

void LightController::controllerConnected()
{
    qDebug() << "connected to controller; discovering services...";
    m_controller->discoverServices();
}

void LightController::controllerDisconnected()
{
    update_message("Controller disconnected");
    qWarning() << "controller disconnected";
}

void LightController::serviceStateChanged(QLowEnergyService::ServiceState state)
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

        const QLowEnergyCharacteristic writeCharacteristic = m_service->characteristic(writeCharacteristicUuid);
        if (!writeCharacteristic.isValid()) {
            update_message("Cannot get write characteristic");
            qDebug() << "cannot get write characteristic";
            break;
        }

        m_command = "U?\n";
        m_service->writeCharacteristic(writeCharacteristic, m_command,  QLowEnergyService::WriteMode::WriteWithoutResponse);

        break;
    }
    default:
        //nothing for now
        break;
    }
}

void LightController::serviceCharacteristicChanged(const QLowEnergyCharacteristic &characteristic, const QByteArray &data)
{
    // ignore any other characteristic change -> shouldn't really happen though
    if (characteristic.uuid() != QBluetoothUuid(readCharacteristicUuid))
        return;

    qDebug() << "received response: " << data;

    updateFromDevice(data);
}

void LightController::serviceDescriptorWritten(const QLowEnergyDescriptor &descriptor, const QByteArray &data)
{
    if (descriptor.isValid()
            && descriptor == m_notificationDescriptor
            && data == QByteArray::fromHex("0000")) {
        // disabled notifications -> assume disconnect intent
        clear();
    }
}

void LightController::serviceError(QLowEnergyService::ServiceError e)
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

void LightController::updateFromDevice(const QByteArray &data)
{
    if(data.startsWith("*")) {
        if(m_command.startsWith("U?")) {
            m_hasReceivedInitialState = true;

            auto controllerType = data.right(2).toInt();
            switch (controllerType) {
            case 2:
                // 2 x Analogic
                update_controllerType(V1_2x10V);
                for (int i = 0; i < 2; ++i) {
                    auto channel = new LightControllerVoltageChannel(QString::number(i+1), this);
                    get_voltageChannels()->append(channel);
                    channel->set_value(data.mid(1 + i*2, 2).toInt());
                }
                break;
            case 3:
                // 4 x PWM
                update_controllerType(V1_4xPWM);
                for (int i = 0; i < 4; ++i) {
                    auto channel = new LightControllerPWMChannel(QString::number(i+1), this);
                    get_pwmChannels()->append(channel);
                    channel->set_value(data.mid(1 + i*2, 2).toInt());
                }
                break;
            default:
                // 1 x PWM + 1 x RGB
                update_controllerType(V1_4xPWM);
                auto pwmChannel = new LightControllerPWMChannel("1", this);
                get_pwmChannels()->append(pwmChannel);
                pwmChannel->set_value(data.mid(1, 2).toInt());

                auto rgbChannel = new LightControllerRGBChannel("2", this);
                get_rgbChannels()->append(rgbChannel);
                rgbChannel->set_redValue(data.mid(3, 2).toInt());
                rgbChannel->set_greenValue(data.mid(5, 2).toInt());
                rgbChannel->set_blueValue(data.mid(7, 2).toInt());
                break;
            }
        } else if(m_command.startsWith("UV")) {
        } else if(m_command.startsWith("UI")) {
        }
    }

    update_isBusy(false);
}

void LightController::updateDevice()
{
    //    m_channel1 = int(m_channel1SliderValue * 0x1F);
    //    m_channel2 = int(m_channel2SliderValue * 0x1F);
    //    m_channel3 = int(m_channel3SliderValue * 0x1F);
    //    m_channel4 = int(m_channel4SliderValue * 0x1F);

    //    QString toSend = QString("US");

    //    toSend.append(QString::number(m_channel1, 16).rightJustified(2, '0'));
    //    toSend.append(QString::number(m_channel2, 16).rightJustified(2, '0'));
    //    toSend.append(QString::number(m_channel3, 16).rightJustified(2, '0'));
    //    toSend.append(QString::number(m_channel4, 16).rightJustified(2, '0'));
    //    toSend.append("03");
    //    toSend.append("\n");

    //    if(toSend.length() != 13) {
    //        qDebug() << "ERROR: BLE SET CMD TO LONG!!!";
    //        return;
    //    }

    //    if (m_lastUartCmd.compare(toSend) != 0) {
    //        qDebug() << "toSend:" << toSend;

    //        m_lastUartCmd = toSend;

    //        emit lightChannelsValueChanged();

    //        if(m_lastUartCmd.contains("U?")) {
    //            m_lastUartCmd = "";
    //        } else {
    //            if(m_haveReceivedUartInitialState) {
    //                qDebug() << "BLE SENDING:" << toSend;
    //                const QLowEnergyCharacteristic uartWriteChar = m_service->characteristic(m_uartWriteCharUuid);
    //                m_service->writeCharacteristic(uartWriteChar, toSend.toUtf8(),  QLowEnergyService::WriteMode::WriteWithoutResponse);
    //            }
    //        }
    //    }
}

} // namespace il
