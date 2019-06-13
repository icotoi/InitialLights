#include "room.h"

#include <QJsonObject>

namespace il {

namespace  {
const QString jsonNameTag { "name" };
}

Room::Room(QObject *parent) : QObject(parent)
{

}

void Room::read(const QJsonObject &json)
{
    if (json.contains(jsonNameTag) && json[jsonNameTag].isString())
        set_name(json[jsonNameTag].toString());
}

void Room::write(QJsonObject &json) const
{
    json[jsonNameTag] = m_name;
}

} // namespace il
