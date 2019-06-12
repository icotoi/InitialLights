#pragma once

#include <QBluetoothDeviceDiscoveryAgent>

#include "QQmlObjectListModel.h"
#include "QQmlVarPropertyHelpers.h"

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
