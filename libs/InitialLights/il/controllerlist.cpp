#include "controllerlist.h"

#include "controller.h"
#include "light.h"

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
    , m_lights { new QQmlObjectListModel<Light>(this) }
{
    connect(&m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, &ControllerList::deviceDiscovered);
    connect(&m_deviceDiscoveryAgent, qOverload<QBluetoothDeviceDiscoveryAgent::Error>(&QBluetoothDeviceDiscoveryAgent::error),
            this, &ControllerList::scanError);
    connect(&m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished,
            this, &ControllerList::scanFinished);

    connect(m_controllers, &QAbstractListModel::rowsInserted, this, &ControllerList::onControllersInserted);
    connect(m_controllers, &QAbstractListModel::rowsAboutToBeRemoved, this, &ControllerList::onControllersAboutToBeRemoved);
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

void ControllerList::onControllersInserted(const QModelIndex &/*parent*/, int first, int last)
{
    for (int index = first; index <= last; ++index) {
        auto controller = m_controllers->at(index);
        if (!controller) {
            qWarning() << "inserted NULL controller";
            return;
        }

        qDebug() << "inserted controller:" << controller->address()
                 << "with" << controller->get_lights()->count() << "lights";

        connect(controller->get_lights(), &QAbstractListModel::rowsInserted, this, &ControllerList::onLightsInserted);
        connect(controller->get_lights(), &QAbstractListModel::rowsAboutToBeRemoved, this, &ControllerList::onLightsAboutToBeRemoved);
    }
}

void ControllerList::onControllersAboutToBeRemoved(const QModelIndex &/*parent*/, int first, int last)
{
    for (int index = first; index <= last; ++index) {
        auto controller = m_controllers->at(index);
        if (!controller) {
            qWarning() << "removing NULL controller";
            return;
        }

        qDebug() << "removing:" << controller->address();

        auto lights = controller->get_lights();
        for(auto it = lights->begin(); it != lights->end(); ++it) {
            auto light = *it;
            qDebug() << "removing light:" << light->lightTypeName();
        }
    }
}

void ControllerList::onLightsInserted(const QModelIndex &/*parent*/, int first, int last)
{

    auto lights = qobject_cast<const QQmlObjectListModelBase*>(sender());
    if (!lights) {
        qWarning() << "trying to use invalid lights model on lights inserted";
        return;
    }

    for (int index = first; index <= last; ++index) {
        auto light = qobject_cast<Light*>(lights->get(index));
        if (!light) {
            qWarning() << "inserted NULL light";
            return;
        }

        qDebug() << "inserted light:" << light->lightTypeName();
    }
}

void ControllerList::onLightsAboutToBeRemoved(const QModelIndex &/*parent*/, int first, int last)
{
    auto lights = qobject_cast<const QQmlObjectListModelBase*>(sender());
    if (!lights) {
        qWarning() << "trying to use invalid lights model on lights about to be removed";
        return;
    }

    for (int index = first; index <= last; ++index) {
        auto light = qobject_cast<Light*>(lights->get(index));
        if (!light) {
            qWarning() << "removing NULL light";
            return;
        }

        qDebug() << "removing light:" << light->lightTypeName();
    }
}

}
