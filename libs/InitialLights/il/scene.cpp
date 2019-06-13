#include "scene.h"

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
    if (json.contains(jsonNameTag) && json[jsonNameTag].isString())
        set_name(json[jsonNameTag].toString());
}

void Scene::write(QJsonObject &json) const
{
    json["name"] = m_name;
}

} // namespace il
