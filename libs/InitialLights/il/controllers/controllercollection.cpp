#include "controllercollection.h"

#include "controller.h"
#include "../jsonhelper.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

namespace il {

namespace {
const QString jsonControllersTag { "controllers" };
}

namespace controllers {

ControllerCollection::ControllerCollection(QObject *parent)
    : QObject(parent)
    , m_items { new QQmlObjectListModel<Controller>(this) }
{
}

ControllerCollection::~ControllerCollection()
{
}

void ControllerCollection::read(const QJsonObject &json)
{
    readCollectionPropertyIfExists<Controller>(json, jsonControllersTag, m_items);
    std::for_each (m_items->begin(), m_items->end(), [this](Controller* controller) {
        connect(controller, &Controller::kindChanged, this, &ControllerCollection::onControllerKindChanged);
    });
}

void ControllerCollection::write(QJsonObject &json) const
{
    writeCollectionProperty(json, jsonControllersTag, m_items);
}

void ControllerCollection::clearLocalData()
{
    m_items->clear();
}

Controller *ControllerCollection::appendNewController()
{
    Controller* controller = new Controller();
    m_items->append(controller);
    connect(controller, &Controller::kindChanged, this, &ControllerCollection::onControllerKindChanged);
    return controller;
}

void ControllerCollection::onControllerKindChanged()
{
    Controller* controller = qobject_cast<Controller*>(sender());
    if (!controller)
        return;
    controllerKindChanged(controller);
}

} // namespace controllers
} // namespace il
