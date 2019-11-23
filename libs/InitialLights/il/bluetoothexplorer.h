#pragma once

#include "ibluetoothexplorer.h"

#include "QQmlVarPropertyHelpers.h"

#include <QBluetoothDeviceDiscoveryAgent>

namespace il {

class ControllerCollection;

class INITIALLIGHTSSHARED_EXPORT BluetoothExplorer : public IBluetoothExplorer
{
    Q_OBJECT

    QML_READONLY_VAR_PROPERTY(bool, isBusy)
    QML_WRITABLE_VAR_PROPERTY(QString, message)
    QML_WRITABLE_VAR_PROPERTY(int, searchTimeout)

public:
    explicit BluetoothExplorer(ControllerCollection* controllers, QObject *parent = nullptr);

public slots:
    void search() override;
    void connectTo(Controller *controller) override;
    void disconnectFrom(Controller *controller) override;
    void readDataFrom(Controller *controller) override;
    void writeDataTo(Controller *controller) override;

    void cancelSearch() override;
    void cancelConnectTo(Controller *controller) override;
    void cancelReadDataFrom(Controller *controller) override;
    void cancelWriteDataTo(Controller *controller) override;

private:
    void deviceDiscovered(const QBluetoothDeviceInfo &info);
    void discoveryFailed(QBluetoothDeviceDiscoveryAgent::Error error);
    void discoveryFinished();

    ControllerCollection* m_controllers;
    QBluetoothDeviceDiscoveryAgent m_deviceDiscoveryAgent;
};

} // namespace il
