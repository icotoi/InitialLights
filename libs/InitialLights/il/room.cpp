#include "room.h"

#include "jsonhelpers.h"

#include <QJsonObject>

namespace il {

namespace  {
const QString jsonNameTag { "name" };
}

Room::Room(QObject *parent)
    : QObject(parent)
{
}

void Room::read(const QJsonObject &json)
{
    safeRead(json, jsonNameTag, [&](const QString& s) { set_name(s); });
}

void Room::write(QJsonObject &json) const
{
    json[jsonNameTag] = m_name;
}

} // namespace il
