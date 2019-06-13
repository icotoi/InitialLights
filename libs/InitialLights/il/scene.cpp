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

void Scene::read(const QJsonObject &json)
{
    safeRead(json, jsonNameTag, [&](const QString& s) { set_name(s); });
}

void Scene::write(QJsonObject &json) const
{
    json["name"] = m_name;
}

} // namespace il
