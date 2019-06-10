#include "lightcontroller.h"
#include "deviceinfo.h"
#include "lightcontrollerpwmchannel.h"

#include <QLowEnergyController>

namespace il {

namespace  {
const QBluetoothUuid uartWriteCharacteristicUuid = QBluetoothUuid(QStringLiteral("6E400002-B5A3-F393-E0A9-E50E24DCCA9E"));
const QBluetoothUuid uartReadCharacteristicUuid = QBluetoothUuid(QStringLiteral("6E400003-B5A3-F393-E0A9-E50E24DCCA9E"));
}

LightController::LightController(DeviceInfo *info, QObject *parent)
    : AbstractLightController (parent)
    , m_info { info }
{
    if (m_info) {
        m_info->setParent(this);
        update_name(m_info->name());
        update_address(m_info->address());
    }
}

LightController::~LightController()
{
    clear();
}

void LightController::clear()
{
    AbstractLightController::clear();
    m_service.reset();

    if (!m_controller.isNull()) {
        m_controller->disconnectFromDevice();
        m_controller.reset();
    }
}

void LightController::connectToController()
{
    update_isBusy(true);

    // just for safety
    clear();

    //    m_measurements.clear();
    //    m_haveReceivedUartInitialState = false;

    m_controller.reset(new QLowEnergyController(m_info->info(), this));

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
    //    m_stop = QDateTime::currentDateTime();

    //    if (m_devices.isEmpty()) {
    //        if (m_timer)
    //            m_timer->stop();
    //        return;
    //    }

    //    //disable notifications before disconnecting
    //    if (m_notificationDesc.isValid()
    //            && m_service
    //            && m_notificationDesc.value() == QByteArray::fromHex("0100")) {
    //        m_service->writeDescriptor(m_notificationDesc, QByteArray::fromHex("0000"));
    //    } else {
    //        m_control->disconnectFromDevice();
    //        delete m_service;
    //        m_service = nullptr;
    //    }
    clear();
}

void LightController::serviceDiscovered(const QBluetoothUuid & uuid)
{
    if (DeviceInfo::isValidService(uuid)) {
        if (m_service.isNull()) {
            update_message("Service found");
            qDebug() << "found service - connecting...";

            m_service.reset(m_controller->createServiceObject(uuid, this));

            connect(m_service.get(), &QLowEnergyService::stateChanged,
                    this, &LightController::serviceStateChanged);
            connect(m_service.get(), &QLowEnergyService::characteristicChanged,
                    this, &LightController::serviceCharacteristicChanged);
            connect(m_service.get(), &QLowEnergyService::descriptorWritten,
                    this, &LightController::serviceDescriptorWritten);
            connect(m_service.get(), qOverload<QLowEnergyService::ServiceError>(&QLowEnergyService::error),
                    this, &LightController::serviceError);

            m_service->discoverDetails();
        } else {
            qWarning() << "service already found";
        }
    }
}

void LightController::serviceScanDone()
{
    qDebug() <<  "service scan done";

    if (m_service.isNull()) {
        update_message("No service found");
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
        const QLowEnergyCharacteristic readCharacteristic = m_service->characteristic(uartReadCharacteristicUuid);
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

        m_start = QDateTime::currentDateTime();

        const QLowEnergyCharacteristic writeCharacteristic = m_service->characteristic(uartWriteCharacteristicUuid);
        if (!writeCharacteristic.isValid()) {
            update_message("Cannot get write characteristic");
            qDebug() << "cannot get write characteristic";
            break;
        }

        m_currentCommand = "U?\n";
        m_service->writeCharacteristic(writeCharacteristic, m_currentCommand,  QLowEnergyService::WriteMode::WriteWithoutResponse);

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
    if (characteristic.uuid() != QBluetoothUuid(uartReadCharacteristicUuid))
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
            m_controller->disconnectFromDevice();
            m_service.reset();
            m_notificationDescriptor = QLowEnergyDescriptor();
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
    //    if(uartStr.startsWith("*")) {
    //        QString data = uartStr.mid(1);

    //        if(m_lastUartCmd.startsWith("U?")) {

    //            if(!m_haveReceivedUartInitialState)
    //                m_haveReceivedUartInitialState = true;

    //            // Current controller values
    //            QString channel1Str = data.mid(0, 2);
    //            m_channel1 = channel1Str.toInt(nullptr, 16);
    //            m_channel1SliderValue = float(m_channel1)/31.00F;

    //            QString channel2Str = data.mid(2, 2);
    //            m_channel2 = channel2Str.toInt(nullptr, 16);
    //            m_channel2SliderValue = (m_channel2 == 0) ? 0 : float(m_channel2)/31.00F;

    //            QString channel3Str = data.mid(4, 2);
    //            m_channel3 = channel3Str.toInt(nullptr, 16);
    //            m_channel3SliderValue = (m_channel3 == 0) ? 0 : float(m_channel3)/31.00F;

    //            QString channel4Str = data.mid(6, 2);
    //            m_channel4 = channel4Str.toInt(nullptr, 16);
    //            m_channel4SliderValue = (m_channel4 == 0) ? 0 : float(m_channel4)/31.00F;

    //            qDebug() << "Channels:" << QString::number(m_channel1) << QString::number(m_channel2) << QString::number(m_channel3) << QString::number(m_channel4);
    //            qDebug() << "Sliders:" << m_channel1SliderValue << m_channel2SliderValue << m_channel3SliderValue << m_channel4SliderValue;

    //            emit lightChannelsValueChanged();

    //        } else if(m_lastUartCmd.startsWith("UV")) {
    //        } else if(m_lastUartCmd.startsWith("UI")) {
    //        }
    //    }
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
