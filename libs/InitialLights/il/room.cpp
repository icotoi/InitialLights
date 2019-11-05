#include "room.h"

#include "jsonhelper.h"

#include <QJsonObject>

namespace il {

namespace {
const int unconfiguredIndex { -1 };

const QString jsonRoomIndex { "index" };
const QString jsonRoomName { "name" };
}

Room::Room(QObject *parent)
    : QObject(parent)
    , m_rid(unconfiguredIndex)
{
}

Room::~Room()
{
}

void Room::read(const QJsonObject &json)
{
    READ_PROPERTY_IF_EXISTS(int, json, jsonRoomIndex, rid)
    READ_PROPERTY_IF_EXISTS(QString, json, jsonRoomName, name)
}

void Room::write(QJsonObject &json) const
{
    json[jsonRoomIndex] = m_rid;
    json[jsonRoomName] = m_name;
}

} // namespace il
