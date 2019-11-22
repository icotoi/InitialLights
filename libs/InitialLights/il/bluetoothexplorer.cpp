#include "bluetoothexplorer.h"

namespace il {

BluetoothExplorer::BluetoothExplorer(QObject *parent)
    : IBluetoothExplorer(parent)
{
}

void BluetoothExplorer::searchControllers()
{
}

void BluetoothExplorer::connectTo(Controller */*controller*/)
{
}

void BluetoothExplorer::disconnectFrom(Controller */*controller*/)
{
}

void BluetoothExplorer::readDataFrom(Controller */*controller*/)
{
}

void BluetoothExplorer::writeDataTo(Controller */*controller*/)
{
}

void BluetoothExplorer::cancelCurrentOperation()
{
}

} // namespace il
