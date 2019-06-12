#include "controllerlist.h"

#include "controller.h"

namespace il {

ControllerList::ControllerList(QObject *parent)
    : QObject (parent)
    , m_isBusy { false }
    , m_scanningTimeout { 3000 }
    , m_controllers { new QQmlObjectListModel<AbstractController>(this) }
{
    connect(&m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, &ControllerList::deviceDiscovered);
    connect(&m_deviceDiscoveryAgent, qOverload<QBluetoothDeviceDiscoveryAgent::Error>(&QBluetoothDeviceDiscoveryAgent::error),
            this, &ControllerList::scanError);
    connect(&m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished,
            this, &ControllerList::scanFinished);
}

ControllerList::~ControllerList()
{
}

void ControllerList::scan()
{
    update_isBusy(true);
    set_message("Scanning for devices...");
    m_controllers->clear();
    m_deviceDiscoveryAgent.setLowEnergyDiscoveryTimeout(m_scanningTimeout);
    m_deviceDiscoveryAgent.start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
}

bool ControllerList::deviceAlreadyScanned(const QBluetoothDeviceInfo &info) const
{
    auto address = Controller::address(info);
    return std::any_of(m_controllers->begin(), m_controllers->end(), [address](AbstractController* controller){
       return controller->address() == address;
    });
}

void ControllerList::deviceDiscovered(const QBluetoothDeviceInfo &info)
{
    if (Controller::isValidDevice(info)) {
        if (!deviceAlreadyScanned(info)) {
            AbstractController* controller = new Controller(info);
            m_controllers->append(controller);
            qWarning() << "LE Device name:" << controller->name()
                       << "address:" << controller->address() << "scanned; adding it to the devices list...";
        }
        set_message("Low Energy device found. Scanning for more...");
    }
    //...
}

void ControllerList::scanError(QBluetoothDeviceDiscoveryAgent::Error error)
{
    switch (error) {
    case QBluetoothDeviceDiscoveryAgent::PoweredOffError:
        set_message("The Bluetooth adaptor is powered off, power it on before doing discovery.");
        break;
    case QBluetoothDeviceDiscoveryAgent::InputOutputError:
        set_message("Writing or reading from the device resulted in an error.");
        break;
    default:
        set_message("An unknown error has occurred.");
    }
}

void ControllerList::scanFinished()
{
    qDebug() << "scan finished";
    update_isBusy(false);
    set_message(m_controllers->size() == 0
               ? "No Low Energy devices found"
               : QString("Found %1 device(s)").arg(m_controllers->size()));
}

}
