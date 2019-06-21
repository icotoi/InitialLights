#pragma once

#include "icodable.h"

#include <QBluetoothDeviceDiscoveryAgent>

#include "QQmlObjectListModel.h"
#include "QQmlVarPropertyHelpers.h"

namespace il {

class Controller;

class INITIALLIGHTSSHARED_EXPORT ControllerList: public QObject, public ICodable
{
    Q_OBJECT

    QML_READONLY_VAR_PROPERTY(bool, isBusy)
    QML_WRITABLE_VAR_PROPERTY(int, scanningTimeout)
    QML_WRITABLE_VAR_PROPERTY(QString, message)
    QML_OBJMODEL_PROPERTY(il::Controller, controllers)

public:
    explicit ControllerList(QObject* parent = nullptr);
    ~ControllerList() override;

    void clear();

    void read(const QJsonObject& json) override;
    void write(QJsonObject& json) const override;

    Controller* findControllerByAddress(const QString& address) const;

public slots:
    void scan();
    void turnScene(int index, bool on);

private:
    bool deviceAlreadyScanned(const QBluetoothDeviceInfo &info) const;

    void deviceDiscovered(const QBluetoothDeviceInfo &info);
    void scanError(QBluetoothDeviceDiscoveryAgent::Error error);
    void scanFinished();

    QBluetoothDeviceDiscoveryAgent m_deviceDiscoveryAgent;
};

}
