#include "lightsuart.h"

namespace il {

struct LightsUart::Impl {
    QQmlListProperty<DeviceInfo> devices;
};

LightsUart::LightsUart(QObject *parent)
    : QObject (parent)
    , m_impl { new Impl }
{
}

LightsUart::~LightsUart()
{
}

QQmlListProperty<DeviceInfo> LightsUart::devices() const
{
    return m_impl->devices;
}

void LightsUart::scan()
{
}

}

//LightsUart::LightsUart()
//    : m_currentDevice(QBluetoothDeviceInfo()),
//      m_foundUartService(false),
//      m_max(0),
//      m_min(0),
//      m_calories(0),
//      m_control(nullptr),
//      m_timer(nullptr),
//      m_service(nullptr)
//{
//    m_deviceDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);

//    connect(m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
//            this, &LightsUart::addDevice);
//    connect(m_deviceDiscoveryAgent, qOverload<QBluetoothDeviceDiscoveryAgent::Error>(&QBluetoothDeviceDiscoveryAgent::error),
//            this, &LightsUart::deviceScanError);
//    connect(m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished,
//            this, &LightsUart::scanFinished);

//    // initialize random seed for demo mode
//    // FIXME: qsrand is obsolete
////    qsrand(QTime::currentTime().msec());
//}

//LightsUart::~LightsUart()
//{
//    qDeleteAll(m_devices);
//    m_devices.clear();
//}

//void LightsUart::deviceSearch()
//{
//    qDeleteAll(m_devices);
//    m_devices.clear();
//    m_deviceDiscoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
//    setMessage("Scanning for devices...");
//}

//void LightsUart::addDevice(const QBluetoothDeviceInfo &device)
//{
//    if (device.serviceUuids().contains(m_uartServiceUuid)) {
//        qWarning() << "Discovered LE Device name: " << device.name() << " Address: "
//                   << device.address().toString();
//        DeviceInfo *dev = new DeviceInfo(device);
//        m_devices.append(dev);
//        setMessage("Low Energy device found. Scanning for more...");
//    }
//    //...
//}

//void LightsUart::scanFinished()
//{
//    if (m_devices.size() == 0)
//        setMessage("No Low Energy devices found");
//    emit nameChanged();
//}

//void LightsUart::deviceScanError(QBluetoothDeviceDiscoveryAgent::Error error)
//{
//    switch (error) {
//    case QBluetoothDeviceDiscoveryAgent::PoweredOffError:
//        setMessage("The Bluetooth adaptor is powered off, power it on before doing discovery.");
//        break;
//    case QBluetoothDeviceDiscoveryAgent::InputOutputError:
//        setMessage("Writing or reading from the device resulted in an error.");
//        break;
//    default:
//        setMessage("An unknown error has occurred.");
//    }
//}

//void LightsUart::setMessage(QString message)
//{
//    if (m_info == message)
//        return;

//    m_info = message;
//    emit messageChanged();
//}

//QVariant LightsUart::name()
//{
//    return QVariant::fromValue(m_devices);
//}

//void LightsUart::setChannel4SliderValue(float value)
//{
//    m_channel4SliderValue = value;
//    updateUartValueState();
//}

//void LightsUart::setChannel3SliderValue(float value)
//{
//    m_channel3SliderValue = value;
//    updateUartValueState();
//}

//void LightsUart::setChannel2SliderValue(float value)
//{
//    m_channel2SliderValue = value;
//    updateUartValueState();
//}

//void LightsUart::setChannel1SliderValue(float value)
//{
//    m_channel1SliderValue = value;
//    updateUartValueState();
//}

//void LightsUart::connectToService(const QString &address)
//{
//    m_measurements.clear();

//    m_haveReceivedUartInitialState = false;

//    bool deviceFound = false;
//    for (int i = 0; i < m_devices.size(); i++) {
//        if (m_devices[i]->getAddress() == address ) {
//            m_currentDevice.setDevice(m_devices[i]->getDevice());
//            setMessage("Connecting to device...");
//            deviceFound = true;
//            break;
//        }
//    }

//    // we are running demo mode
//    if (!deviceFound) {
//        startDemo();
//        return;
//    }

//    if (m_control) {
//        m_control->disconnectFromDevice();
//        delete m_control;
//        m_control = nullptr;
//    }

//    m_control = new QLowEnergyController(m_currentDevice.getDevice(), this);

//    connect(m_control, &QLowEnergyController::serviceDiscovered,
//            this, &LightsUart::serviceDiscovered);
//    connect(m_control, &QLowEnergyController::discoveryFinished,
//            this, &LightsUart::serviceScanDone);
//    connect(m_control, qOverload<QLowEnergyController::Error>(&QLowEnergyController::error),
//            this, &LightsUart::controllerError);
//    connect(m_control, &QLowEnergyController::connected,
//            this, &LightsUart::deviceConnected);
//    connect(m_control, &QLowEnergyController::disconnected,
//            this, &LightsUart::deviceDisconnected);

//    m_control->connectToDevice();
//}

//void LightsUart::deviceConnected()
//{
//    m_control->discoverServices();
//}

//void LightsUart::deviceDisconnected()
//{
//    setMessage("Heart Rate service disconnected");
//    qWarning() << "Remote device disconnected";
//}

//void LightsUart::serviceDiscovered(const QBluetoothUuid &gatt)
//{
//    if (gatt == m_uartServiceUuid) {
//        setMessage("UART service discovered. Waiting for service scan to be done...");
//        qDebug() << "UART service discovered. Waiting for service scan to be done...";
//        m_foundUartService = true;
//    }
//}

//void LightsUart::serviceScanDone()
//{
//    delete m_service;
//    m_service = nullptr;

//    if (m_foundUartService) {
//        setMessage("Connecting to service...");
//        m_service = m_control->createServiceObject(m_uartServiceUuid, this);
//    }

//    if (!m_service) {
//        setMessage("UART Service not found.");
//        return;
//    }

//    connect(m_service, &QLowEnergyService::stateChanged,
//            this, &LightsUart::serviceStateChanged);
//    connect(m_service, &QLowEnergyService::characteristicChanged,
//            this, &LightsUart::receivedUartResponse);
//    connect(m_service, &QLowEnergyService::descriptorWritten,
//            this, &LightsUart::confirmedDescriptorWrite);

//    m_service->discoverDetails();
//}

//void LightsUart::disconnectService()
//{
//    m_foundUartService = false;
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
//}

//void LightsUart::controllerError(QLowEnergyController::Error error)
//{
//    setMessage("Cannot connect to remote device.");
//    qWarning() << "Controller Error:" << error;
//}

//void LightsUart::serviceStateChanged(QLowEnergyService::ServiceState s)
//{
//    qDebug() << "aici";
//    switch (s) {
//    case QLowEnergyService::ServiceDiscovered: {
//        qDebug() << "aici 3";

//        const QLowEnergyCharacteristic uartChar = m_service->characteristic(m_uartReadCharUuid);
//        if (!uartChar.isValid()) {
//            setMessage("UART Data not found.");
//            qDebug() << "UART Data not found.";
//            break;
//        }

//        qDebug() << "serviceStateChanged";

//        m_notificationDesc = uartChar.descriptor(QBluetoothUuid::ClientCharacteristicConfiguration);
//        if (m_notificationDesc.isValid()) {
//            qDebug() << "aici 2222";

//            m_service->writeDescriptor(m_notificationDesc, QByteArray::fromHex("0100"));
//            setMessage("Connected");
//            m_start = QDateTime::currentDateTime();

//            const QLowEnergyCharacteristic uartWriteChar = m_service->characteristic(m_uartWriteCharUuid);
//            m_lastUartCmd = QString("U?\n");
//            m_service->writeCharacteristic(uartWriteChar, m_lastUartCmd.toUtf8(),  QLowEnergyService::WriteMode::WriteWithoutResponse);
//        }
//        break;
//    }
//    default:
//        //nothing for now
//        break;
//    }
//}

//void LightsUart::serviceError(QLowEnergyService::ServiceError e)
//{
//    switch (e) {
//    case QLowEnergyService::DescriptorWriteError:
//        setMessage("Cannot obtain HR notifications");
//        break;
//    default:
//        qWarning() << "HR service error:" << e;
//    }
//}

//void LightsUart::receivedUartResponse(const QLowEnergyCharacteristic &c,
//                                      const QByteArray &value)
//{
//    // ignore any other characteristic change -> shouldn't really happen though
//    if (c.uuid() != QBluetoothUuid(m_uartReadCharUuid))
//        return;

//    QString uartResponse = QString(value);

//    qDebug() << "receivedUartResponse: " << uartResponse;

//    updateFromUartValues(uartResponse);
//}

//void LightsUart::confirmedDescriptorWrite(const QLowEnergyDescriptor &d,
//                                          const QByteArray &value)
//{
//    if (d.isValid() && d == m_notificationDesc && value == QByteArray::fromHex("0000")) {
//        //disabled notifications -> assume disconnect intent
//        m_control->disconnectFromDevice();
//        delete m_service;
//        m_service = nullptr;
//    }
//}

//void LightsUart::obtainResults()
//{
//}

//int LightsUart::measurements(int index) const
//{
//    if (index > m_measurements.size())
//        return 0;
//    else
//        return m_measurements.value(index);
//}

//int LightsUart::measurementsSize() const
//{
//    return m_measurements.size();
//}

//QString LightsUart::deviceAddress() const
//{
//    return m_currentDevice.getAddress();
//}

//int LightsUart::numDevices() const
//{
//    return m_devices.size();
//}

//void LightsUart::startDemo()
//{
//    m_start = QDateTime::currentDateTime();
//    if (!m_timer) {
//        m_timer = new QTimer(this);
//        connect(m_timer, &QTimer::timeout, this, &LightsUart::receiveDemo);
//    }
//    m_timer->start(1000);
//    setMessage("This is Demo mode");
//}

//void LightsUart::receiveDemo()
//{
//    m_measurements.append(randomPulse());
//    emit lightChannelsValueChanged();
//}

//quint16 LightsUart::randomPulse() const
//{
//    // random number between 50 and 70
//    return qrand() % (70 - 50) + 50;
//}

//void LightsUart::updateUartValueState()
//{
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

//}

//void LightsUart::updateFromUartValues(QString uartStr)
//{
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
//}
