#pragma once

#include "ibluetoothexplorer.h"

#include <QBluetoothDeviceDiscoveryAgent>

namespace il {

namespace controllers {
class ControllerCollection;
}

namespace bluetooth {

class INITIALLIGHTSSHARED_EXPORT BluetoothExplorer : public IBluetoothExplorer
{
    Q_OBJECT

public:
    explicit BluetoothExplorer(controllers::ControllerCollection* controllers, QObject *parent = nullptr);

public slots:
    void search() override;

private:
    void deviceDiscovered(const QBluetoothDeviceInfo &info);
    void discoveryFailed(QBluetoothDeviceDiscoveryAgent::Error error);
    void discoveryFinished();

    controllers::ControllerCollection* m_controllers;
    QBluetoothDeviceDiscoveryAgent m_deviceDiscoveryAgent;
};

} // namespace bluetooth
} // namespace il
