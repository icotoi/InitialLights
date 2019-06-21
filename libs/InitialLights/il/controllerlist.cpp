#include "controllerlist.h"

#include "controller.h"

#include <QJsonArray>
#include <QJsonObject>

namespace il {

namespace  {
const QString jsonControllersTag { "controllers" };
}

ControllerList::ControllerList(QObject *parent)
    : QObject (parent)
    , m_isBusy { false }
    , m_scanningTimeout { 3000 }
    , m_controllers { new QQmlObjectListModel<Controller>(this) }
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

void ControllerList::clear()
{
    m_controllers->clear();
}

void ControllerList::read(const QJsonObject &json)
{
    if (json.contains(jsonControllersTag) && json[jsonControllersTag].isArray()) {
        QJsonArray controllerArray { json[jsonControllersTag].toArray() };
        m_controllers->clear();
        for (int i = 0; i < controllerArray.size(); ++i) {
            QJsonObject controllerObject = controllerArray[i].toObject();
            auto controller = new Controller;
            controller->read(controllerObject);
            m_controllers->append(controller);
        }
    }
}

void ControllerList::write(QJsonObject &json) const
{
    QJsonArray controllerArray;
    for(int i = 0; i < m_controllers->size(); ++i) {
        auto controller = m_controllers->at(i);
        QJsonObject controllerObject;
        controller->write(controllerObject);
        controllerArray.append(controllerObject);
    }
    json[jsonControllersTag] = controllerArray;
}

Controller *ControllerList::findControllerByAddress(const QString &address) const
{
    for(int i = 0; i < m_controllers->size(); ++i) {
        auto controller = m_controllers->at(i);
        if (controller->address() == address) {
            return controller;
        }
    }
    return nullptr;
}

void ControllerList::scan()
{
    update_isBusy(true);
    set_message("Scanning for devices...");
    m_controllers->clear();
    m_deviceDiscoveryAgent.setLowEnergyDiscoveryTimeout(m_scanningTimeout);
    m_deviceDiscoveryAgent.start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
}

void ControllerList::turnScene(int index, bool on)
{
    for(int i = 0; i < m_controllers->count(); ++i) {
        auto controller = m_controllers->at(i);
        controller->turnScene(index, on);
    }
}

bool ControllerList::deviceAlreadyScanned(const QBluetoothDeviceInfo &info) const
{
    auto address = Controller::safeAddress(info);
    return std::any_of(m_controllers->begin(), m_controllers->end(), [address](Controller* controller){
        return controller->address() == address;
    });
}

void ControllerList::deviceDiscovered(const QBluetoothDeviceInfo &info)
{
    if (Controller::isValidDevice(info)) {
        if (!deviceAlreadyScanned(info)) {
            Controller* controller = new Controller(info);
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
