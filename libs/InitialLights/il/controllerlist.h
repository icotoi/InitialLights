#pragma once

#include "initiallights_global.h"

#include <QBluetoothDeviceDiscoveryAgent>

#include "QQmlObjectListModel.h"
#include "QQmlVarPropertyHelpers.h"

namespace il {

class Controller;
class Light;

class INITIALLIGHTSSHARED_EXPORT ControllerList: public QObject
{
    Q_OBJECT

    QML_READONLY_VAR_PROPERTY(bool, isBusy)
    QML_WRITABLE_VAR_PROPERTY(int, scanningTimeout)
    QML_WRITABLE_VAR_PROPERTY(QString, message)
    QML_OBJMODEL_PROPERTY(il::Controller, controllers)
    QML_OBJMODEL_PROPERTY(il::Light, lights)

public:
    explicit ControllerList(QObject* parent = nullptr);
    virtual ~ControllerList();

    void clear();

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;

public slots:
    void scan();

private:
    bool deviceAlreadyScanned(const QBluetoothDeviceInfo &info) const;

    void deviceDiscovered(const QBluetoothDeviceInfo &info);
    void scanError(QBluetoothDeviceDiscoveryAgent::Error error);
    void scanFinished();

    void onControllersInserted(const QModelIndex &parent, int first, int last);
    void onControllersAboutToBeRemoved(const QModelIndex &parent, int first, int last);

    void onLightsInserted(const QModelIndex &parent, int first, int last);
    void onLightsAboutToBeRemoved(const QModelIndex &parent, int first, int last);

    QBluetoothDeviceDiscoveryAgent m_deviceDiscoveryAgent;
};

}
