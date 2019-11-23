#include "bluetoothexplorer.h"
#include "controller.h"
#include "controllercollection.h"

#include <QTimer>

namespace il {

BluetoothExplorer::BluetoothExplorer(ControllerCollection* controllers, QObject *parent)
    : IBluetoothExplorer(parent)
    , m_controllers(controllers)
{
}

void BluetoothExplorer::search()
{
    // TODO
    QTimer::singleShot(3000, [this](){
        m_controllers->get_items()->clear();
        Controller* controller = m_controllers->appendNewController();
        controller->set_name("Foo");
        controller->set_address("ACCF24634326FA12");
        controller->set_state(Controller::Enabled);

        controller = m_controllers->appendNewController();
        controller->set_name("Bar");
        controller->set_address("ACCF24634326FA14");
        controller->set_state(Controller::Disabled);

        controller = m_controllers->appendNewController();
        controller->set_name("Unnamed");
        controller->set_address("ACCF24634326FA16");
        controller->set_state(Controller::NotConfigured);

        controller = m_controllers->appendNewController();
        controller->set_name("Baz");
        controller->set_address("ACCF24634326FA18");
        controller->set_state(Controller::Offline);

        emit searchFinished();
    });
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

void BluetoothExplorer::cancelSearch()
{

}

void BluetoothExplorer::cancelConnectTo(Controller */*controller*/)
{

}

void BluetoothExplorer::cancelReadDataFrom(Controller */*controller*/)
{

}

void BluetoothExplorer::cancelWriteDataTo(Controller */*controller*/)
{

}

} // namespace il
