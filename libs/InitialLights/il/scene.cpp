#include "scene.h"

#include <QJsonObject>

namespace il {

Scene::Scene(QObject *parent) : QObject(parent)
{

}

void Scene::write(QJsonObject &json) const
{
    json["name"] = m_name;
}

} // namespace il
