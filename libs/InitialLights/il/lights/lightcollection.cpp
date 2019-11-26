#include "analogiclight.h"
#include "lightcollection.h"

#include "analogiclight.h"
#include "rgbwlight.h"
#include "../controllers/controller.h"
#include "../iindexer.h"
#include "../jsonhelper.h"

namespace il {

namespace {
const QString jsonLightsTag { "lights" };
}

template<>
void readCollectionPropertyIfExists<lights::ILight>(const QJsonObject& json, const QString& tag, QQmlObjectListModel<lights::ILight>* property)
{
    using namespace il::lights;
    if (json.contains(tag) && json[tag].isArray()) {
        QJsonArray jsonArray = json[tag].toArray();
        property->clear();
        if (jsonArray.empty()) return;
        for (int i = 0; i < jsonArray.size(); ++i) {
            QJsonObject jsonObject = jsonArray[i].toObject();
            LightKind::Kind kind = LightKind::kind(json);
            lights::LightBase* object { nullptr };
            switch (kind) {
            case il::lights::LightKind::RGBW:
                object = new RGBWLight;
                break;
            case il::lights::LightKind::Analogic:
                object = new AnalogicLight;
                break;
            case il::lights::LightKind::Unknown:
                continue;
            }
            object->read(jsonObject);
            property->append(object);
        }
    }
}

namespace lights {

LightCollection::LightCollection(controllers::Controller* controller, QObject *parent)
    : QObject(parent)
    , m_items { new QQmlObjectListModel<ILight>(this) }
    , m_controller { controller }
{
}

LightCollection::~LightCollection()
{
}

void LightCollection::read(const QJsonObject &json)
{
    readCollectionPropertyIfExists<ILight>(json, jsonLightsTag, m_items);

    if (m_controller) {
        std::for_each(m_items->begin(),
                      m_items->end(),
                      [this](ILight* light) { light->update_controller(m_controller); });
    }
}

void LightCollection::write(QJsonObject &json) const
{
    writeCollectionProperty(json, jsonLightsTag, m_items);
}

void LightCollection::clearLocalData()
{
    m_items->clear();
}

ILight *LightCollection::appendNewLight(LightKind::Kind kind)
{
    ILight* light { nullptr };
    switch (kind) {
    case LightKind::RGBW:
        light = new RGBWLight;
        break;
    case LightKind::Analogic:
        light = new AnalogicLight;
        break;
    case LightKind::Unknown:
        return nullptr;
    }

    light->update_controller(m_controller);
    m_items->append(light);
    return light;
}

} // namespace lights
} // namespace il
