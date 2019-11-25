#pragma once

#include "ibluetoothexplorer.h"

#include <QBluetoothDeviceDiscoveryAgent>

namespace il {

class ControllerCollection;

class INITIALLIGHTSSHARED_EXPORT BluetoothExplorer : public IBluetoothExplorer
{
    Q_OBJECT

public:
    explicit BluetoothExplorer(ControllerCollection* controllers, QObject *parent = nullptr);

public slots:
    void search() override;

private:
    void deviceDiscovered(const QBluetoothDeviceInfo &info);
    void discoveryFailed(QBluetoothDeviceDiscoveryAgent::Error error);
    void discoveryFinished();

    ControllerCollection* m_controllers;
    QBluetoothDeviceDiscoveryAgent m_deviceDiscoveryAgent;
};

} // namespace il
