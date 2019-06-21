#include "scene.h"

#include "jsonhelpers.h"

#include <QJsonObject>

namespace il {

namespace  {
const QString jsonNameTag { "name" };
}

Scene::Scene(QObject *parent)
    : QObject(parent)
{
}

Scene::~Scene()
{
}

void Scene::read(const QJsonObject &json)
{
    safeRead(json, jsonNameTag, QJsonValue::String, [&](const QJsonValue& json) { set_name(json.toString()); });
}

void Scene::write(QJsonObject &json) const
{
    json["name"] = m_name;
}

} // namespace il
