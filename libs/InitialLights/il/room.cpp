#include "room.h"

#include "light.h"
#include "controller.h"
#include "controllerlist.h"
#include "jsonhelpers.h"

#include <QJsonObject>

namespace il {

namespace  {
const QString jsonNameTag { "name" };
const QString jsonLightsTag { "lights" };
const QString jsonControllerAddressTag { "controllerAddress" };
const QString jsonLightIndexTag { "lightIndex" };
}

Room::Room(ControllerList* controllerList, QObject *parent)
    : QObject(parent)
    , m_lights { new QQmlObjectListModel<Light>(this) }
    , m_controllerList { controllerList }
{
}

void Room::read(const QJsonObject &json)
{
    safeRead(json, jsonNameTag, QJsonValue::String, [&](const QJsonValue& json) { set_name(json.toString()); });

    readModel<Light>(json, jsonLightsTag, m_lights, [&](const QJsonObject& json) {
        QString address;
        int index = -1;
        safeRead(json, jsonControllerAddressTag, QJsonValue::String, [&](const QJsonValue& json) { address = json.toString(); });
        safeRead(json, jsonLightIndexTag, QJsonValue::Double, [&](const QJsonValue& json) { index = json.toInt(); });
        if (address.isEmpty() || index < 0) {
            return;
        }

        auto controller = m_controllerList->findControllerByAddress(address);
        if (!controller) {
            qWarning() << "could not find controller with address" << address;
            return;
        }

        auto lights = controller->get_lights();
        if (index >= lights->count()) {
            qWarning() << "could not find light" << (index + 1) << "- controller" << address << "only has" << lights->count() << "lights";
            return;
        }

        auto light = lights->at(index);
        if (light->room()) {
            qWarning() << "light already assigned to room" << light->room()->name();
            qWarning() << "room" << this->name() << "has" << m_lights->count() << "lights";
            return;
        }

        light->setRoom(this);
    });
}

void Room::write(QJsonObject &json) const
{
    json[jsonNameTag] = m_name;

    writeModel<Light>(json, jsonLightsTag, m_lights, [&](QJsonObject& json, const Light* light) {
        auto controller = qobject_cast<Controller*>(light->controller());
        if (!controller) {
            qWarning() << "could not save room light without controller";
            return;
        }

        auto index = controller->get_lights()->indexOf(const_cast<Light*>(light));
        if (index < 0) {
            qWarning() << "could not find room light in controller:" << controller->address();
        }

        json[jsonControllerAddressTag] = controller->address();
        json[jsonLightIndexTag] = index;
    });
}

} // namespace il
