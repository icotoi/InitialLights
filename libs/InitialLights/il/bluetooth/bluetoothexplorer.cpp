#include "bluetoothexplorer.h"
#include "../bluetooth/bluetoothcontroller.h"
#include "../controllers/controller.h"
#include "../controllers/controllercollection.h"

#include <QTimer>

#include <QBluetoothUuid>
#if !defined (Q_OS_MAC)
#include <QBluetoothAddress>
#endif

namespace il {

namespace {

const QBluetoothUuid uuidService(QStringLiteral("F0001110-0451-4000-B000-000000000000")); // controller service UUID

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

void configureController(controllers::Controller *controller, const QBluetoothDeviceInfo &info)
{
    controller->set_name(info.name());
    controller->set_address(safeAddress(info));
    controller->set_isOnline(true);
}

controllers::Controller* findController(controllers::ControllerCollection* controllers, const QBluetoothDeviceInfo &info)
{
    QString address = safeAddress(info);
    auto items = controllers->get_items();
    auto iterator = std::find_if(items->begin(), items->end(), [address](controllers::Controller* controller) {
        return controller->address() == address;
    });
    return iterator != items->end() ? *iterator : nullptr;
}

} // namescape

namespace bluetooth {

BluetoothExplorer::BluetoothExplorer(controllers::ControllerCollection* controllers, QObject *parent)
    : IBluetoothExplorer(parent)
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
    if (isSearching()) {
//        qDebug() << "already searching; ignore new search request...";
        return;
    }

    m_onlineControllers.clear();
    update_isSearching(true);
    set_message("Searching for controllers...");

    m_deviceDiscoveryAgent.setLowEnergyDiscoveryTimeout(searchTimeout());
    m_deviceDiscoveryAgent.start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
}

void BluetoothExplorer::updateOfflineControllers()
{
    QSet<controllers::Controller*> controllers = QSet(m_controllers->get_items()->begin(), m_controllers->get_items()->end());
//    QSet<controllers::Controller*> controllers = m_controllers->get_items()->toList().toSet();
    controllers.subtract(m_onlineControllers);
    std::for_each(controllers.begin(), controllers.end(),
                  [](controllers::Controller* controller) {
                      if (controller->isOnline()) {
                          qDebug() << "lost connection to" << controller->name() << "(offline)";
                          controller->set_isOnline(false);
                      }
                  });
}

void BluetoothExplorer::deviceDiscovered(const QBluetoothDeviceInfo &info)
{
//    qDebug() << "??? device discovered:" << safeAddress(info);
    if (isValidDevice(info)) {
        controllers::Controller* controller = findController(m_controllers, info);
        if (controller) {
            if (!controller->isOnline()) {
                qDebug() << "setting controller to online:" << controller->name() << controller->address();
                controller->set_isOnline(true);
                controller->bluetoothController()->connectToController(info);
            }
            m_onlineControllers << controller;
        } else {
            auto bluetoothController = new BluetoothController;
            controller = m_controllers->appendNewController(bluetoothController);
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
    updateOfflineControllers();

//    qDebug() << "search finished";
    update_isSearching(false);
    set_message(m_controllers->get_items()->size() == 0
                    ? "No Low Energy devices found"
                    : QString("Found %1 device(s)").arg(m_controllers->get_items()->size()));
    emit searchFinished();
}

} // namespace bluetooth
} // namespace il
