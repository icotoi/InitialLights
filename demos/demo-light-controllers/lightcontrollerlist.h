#pragma once

#include <QBluetoothDeviceDiscoveryAgent>
#include <QQmlListProperty>

#include "QQmlObjectListModel.h"
#include "QQmlVarPropertyHelpers.h"

//#include <QDateTime>
//#include <QVector>
//#include <QTimer>
//#include <QBluetoothDeviceDiscoveryAgent>
//#include <QBluetoothDeviceInfo>
//#include <QLowEnergyController>
//#include <QLowEnergyService>

namespace il {

class AbstractLightController;
class DeviceInfo;

class LightControllerList: public QObject
{
    Q_OBJECT

    QML_READONLY_VAR_PROPERTY(bool, scanning)
    QML_WRITABLE_VAR_PROPERTY(int, scanningTimeout)
    QML_WRITABLE_VAR_PROPERTY(QString, message)
    QML_OBJMODEL_PROPERTY(il::AbstractLightController, controllers)

public:
    explicit LightControllerList(QObject* parent = nullptr);
    virtual ~LightControllerList();

public slots:
    void scan();

private:
    bool deviceAlreadyScanned(const QBluetoothDeviceInfo &info) const;

    void deviceDiscovered(const QBluetoothDeviceInfo &info);
    void scanError(QBluetoothDeviceDiscoveryAgent::Error error);
    void scanFinished();

    void createDummyControllers();

    QBluetoothDeviceDiscoveryAgent m_deviceDiscoveryAgent;
};

}

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

//    //DemoMode
//    void receiveDemo();

//    quint16 randomPulse() const;
//    void updateUartValueState();
//    void updateFromUartValues(QString uartStr);

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
//    QTimer *m_timer; // for demo application
//    QLowEnergyService *m_service;

//    QString m_lastUartCmd;
//    bool m_haveReceivedUartInitialState;
//};
