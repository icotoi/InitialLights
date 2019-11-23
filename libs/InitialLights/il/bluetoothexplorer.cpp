#include "bluetoothexplorer.h"
#include "controller.h"
#include "controllercollection.h"

#include <QTimer>

#if defined (Q_OS_MAC)
#include <QBluetoothUuid>
#else
#include <QBluetoothAddress>
#endif

namespace il {

namespace {

const QBluetoothUuid uuidService(QStringLiteral("F0001110-0451-4000-B000-000000000000"));

QString safeAddress(const QBluetoothDeviceInfo &info)
{
#if defined(Q_OS_MAC)
    // workaround for Core Bluetooth:
    return info.deviceUuid().toString();
#else
    return info.address().toString();
#endif
}

bool isValidDevice(const QBluetoothDeviceInfo &info)
{
    return info.serviceUuids().contains(uuidService);
}

void configureController(Controller *controller, const QBluetoothDeviceInfo &info)
{
    controller->set_name(info.name());
    controller->set_address(safeAddress(info));
    controller->set_isOnline(true);
}

Controller* findController(ControllerCollection* controllers, const QBluetoothDeviceInfo &info)
{
    QString address = safeAddress(info);
    auto items = controllers->get_items();
    auto iterator = std::find_if(items->begin(), items->end(), [address](Controller* controller) {
        return controller->address() == address;
    });
    return iterator != items->end() ? *iterator : nullptr;
}

void setControllersOffline(ControllerCollection* controllers)
{
    auto items = controllers->get_items();
    std::for_each(items->begin(), items->end(), [](Controller* controller) {
        controller->set_isOnline(false);
    });
}

} // namescape

BluetoothExplorer::BluetoothExplorer(ControllerCollection* controllers, QObject *parent)
    : IBluetoothExplorer(parent)
    , m_isBusy { false }
    , m_searchTimeout { 3000 }
    , m_controllers { controllers }
{
    connect(&m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, &BluetoothExplorer::deviceDiscovered);
    connect(&m_deviceDiscoveryAgent, qOverload<QBluetoothDeviceDiscoveryAgent::Error>(&QBluetoothDeviceDiscoveryAgent::error),
            this, &BluetoothExplorer::discoveryFailed);
    connect(&m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished,
            this, &BluetoothExplorer::discoveryFinished);
}

void BluetoothExplorer::search()
{
    update_isBusy(true);
    set_message("Searching for controllers...");

    setControllersOffline(m_controllers);

    m_deviceDiscoveryAgent.setLowEnergyDiscoveryTimeout(m_searchTimeout);
    m_deviceDiscoveryAgent.start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
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

void BluetoothExplorer::deviceDiscovered(const QBluetoothDeviceInfo &info)
{
    if (isValidDevice(info)) {
        Controller* controller = findController(m_controllers, info);
        if (controller) {
            qDebug() << "setting controller to online:" << controller->name() << controller->address();
            controller->set_isOnline(true);
        } else {
            controller = m_controllers->appendNewController();
            configureController(controller, info);
            qWarning() << "LE Device name:" << controller->name()
                       << "address:" << controller->address() << "scanned; adding it to the devices list...";
        }
        set_message("Low Energy device found. Scanning for more...");
    }
    //...
}

void BluetoothExplorer::discoveryFailed(QBluetoothDeviceDiscoveryAgent::Error error)
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

void BluetoothExplorer::discoveryFinished()
{
    qDebug() << "scan finished";
    update_isBusy(false);
    set_message(m_controllers->get_items()->size() == 0
                    ? "No Low Energy devices found"
                    : QString("Found %1 device(s)").arg(m_controllers->get_items()->size()));
    emit searchFinished();
}

} // namespace il
