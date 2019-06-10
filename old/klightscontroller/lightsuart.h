#pragma once

#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothUuid>
#include <QQmlListProperty>

#include "deviceinfo.h"
#include "qt-qml-models/QQmlObjectListModel.h"

//#include <QDateTime>
//#include <QVector>
//#include <QTimer>
//#include <QBluetoothDeviceDiscoveryAgent>
//#include <QBluetoothDeviceInfo>
//#include <QLowEnergyController>
//#include <QLowEnergyService>

namespace il {

class LightsUart: public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool scanning READ scanning NOTIFY scanningChanged)
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)
    QML_OBJMODEL_PROPERTY(DeviceInfo, devices)

public:
    explicit LightsUart(QObject* parent = nullptr);
    virtual ~LightsUart();

    bool scanning() const { return m_scanning; }
    QString message() const { return m_message; }

public slots:
    void scan();

signals:
    void scanningChanged(bool scanning);
    void messageChanged(QString message);

private:
    void setScanning(bool scanning);
    void setMessage(QString message);

    bool deviceAlreadyScanned(const QBluetoothDeviceInfo &device) const;

    void deviceDiscovered(const QBluetoothDeviceInfo &device);
    void scanError(QBluetoothDeviceDiscoveryAgent::Error error);
    void scanFinished();

    const QBluetoothUuid m_uartServiceUuid = QBluetoothUuid(QStringLiteral("6E400001-B5A3-F393-E0A9-E50E24DCCA9E"));
    const QBluetoothUuid m_uartWriteCharUuid = QBluetoothUuid(QStringLiteral("6E400002-B5A3-F393-E0A9-E50E24DCCA9E"));
    const QBluetoothUuid m_uartReadCharUuid = QBluetoothUuid(QStringLiteral("6E400003-B5A3-F393-E0A9-E50E24DCCA9E"));

    bool m_scanning = false;
    QString m_message;

    QBluetoothDeviceDiscoveryAgent m_deviceDiscoveryAgent;
};

}

//class LightsUart: public QObject
//{
//    Q_OBJECT
//    Q_PROPERTY(QVariant name READ name NOTIFY nameChanged)
//    Q_PROPERTY(QString message READ message NOTIFY messageChanged)

//    Q_PROPERTY(int channel1 READ getChannel1 NOTIFY lightChannelsValueChanged)
//    Q_PROPERTY(int channel2 READ getChannel2 NOTIFY lightChannelsValueChanged)
//    Q_PROPERTY(int channel3 READ getChannel3 NOTIFY lightChannelsValueChanged)
//    Q_PROPERTY(int channel4 READ getChannel4 NOTIFY lightChannelsValueChanged)

//    Q_PROPERTY(float channel1SliderValue READ getChannel1SliderValue WRITE setChannel1SliderValue NOTIFY lightChannelsValueChanged)
//    Q_PROPERTY(float channel2SliderValue READ getChannel2SliderValue WRITE setChannel2SliderValue NOTIFY lightChannelsValueChanged)
//    Q_PROPERTY(float channel3SliderValue READ getChannel3SliderValue WRITE setChannel3SliderValue NOTIFY lightChannelsValueChanged)
//    Q_PROPERTY(float channel4SliderValue READ getChannel4SliderValue WRITE setChannel4SliderValue NOTIFY lightChannelsValueChanged)

//public:
//    LightsUart();
//    ~LightsUart();

//    QVariant name();

//    int getChannel1() const { return m_channel1; }
//    int getChannel2() const { return m_channel2; }
//    int getChannel3() const { return m_channel3; }
//    int getChannel4() const { return m_channel4; }

//    void setMessage(QString message);
//    QString message() const { return m_info; }

//    float getChannel1SliderValue() const { return m_channel1SliderValue; }
//    void setChannel1SliderValue(float value);

//    float getChannel2SliderValue() const { return m_channel2SliderValue; }
//    void setChannel2SliderValue(float value);

//    float getChannel3SliderValue() const { return m_channel3SliderValue; }
//    void setChannel3SliderValue(float value);

//    float getChannel4SliderValue() const { return m_channel4SliderValue; }
//    void setChannel4SliderValue(float value);

//signals:
//    void messageChanged();
//    void nameChanged();
//    void lightChannelsValueChanged();

//public slots:
//    void deviceSearch();
//    void connectToService(const QString &address);
//    void disconnectService();
//    void startDemo();

//    void obtainResults();
//    int measurements(int index) const;
//    int measurementsSize() const;
//    QString deviceAddress() const;
//    int numDevices() const;

//private:
//    //QBluetothDeviceDiscoveryAgent
//    void addDevice(const QBluetoothDeviceInfo&);
//    void scanFinished();
//    void deviceScanError(QBluetoothDeviceDiscoveryAgent::Error);

//    //QLowEnergyController
//    void serviceDiscovered(const QBluetoothUuid &);
//    void serviceScanDone();
//    void controllerError(QLowEnergyController::Error);
//    void deviceConnected();
//    void deviceDisconnected();

//    //QLowEnergyService
//    void serviceStateChanged(QLowEnergyService::ServiceState s);
//    void receivedUartResponse(const QLowEnergyCharacteristic &c,
//                              const QByteArray &value);
//    void confirmedDescriptorWrite(const QLowEnergyDescriptor &d,
//                              const QByteArray &value);
//    void serviceError(QLowEnergyService::ServiceError e);

//    //DemoMode
//    void receiveDemo();

//    quint16 randomPulse() const;
//    void updateUartValueState();
//    void updateFromUartValues(QString uartStr);

//    int m_channel1;
//    int m_channel2;
//    int m_channel3;
//    int m_channel4;

//    float m_channel1SliderValue;
//    float m_channel2SliderValue;
//    float m_channel3SliderValue;
//    float m_channel4SliderValue;

//    const QBluetoothUuid m_uartServiceUuid = QBluetoothUuid(QStringLiteral("6E400001-B5A3-F393-E0A9-E50E24DCCA9E"));
//    const QBluetoothUuid m_uartWriteCharUuid = QBluetoothUuid(QStringLiteral("6E400002-B5A3-F393-E0A9-E50E24DCCA9E"));
//    const QBluetoothUuid m_uartReadCharUuid = QBluetoothUuid(QStringLiteral("6E400003-B5A3-F393-E0A9-E50E24DCCA9E"));

//    DeviceInfo m_currentDevice;
//    QBluetoothDeviceDiscoveryAgent *m_deviceDiscoveryAgent;
//    QLowEnergyDescriptor m_notificationDesc;
//    QList<DeviceInfo*> m_devices;
//    QString m_info;
//    bool m_foundUartService;
//    QVector<quint16> m_measurements;
//    QDateTime m_start;
//    QDateTime m_stop;
//    int m_max;
//    int m_min;
//    float m_calories;
//    QLowEnergyController *m_control;
//    QTimer *m_timer; // for demo application
//    QLowEnergyService *m_service;

//    QString m_lastUartCmd;
    //    bool m_haveReceivedUartInitialState;
//};
