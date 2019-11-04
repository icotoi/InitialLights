#include "roomcollection.h"

#include "jsonhelper.h"
#include "room.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

namespace il {

namespace {
const QString jsonRoomsTag { "rooms" };
}

RoomCollection::RoomCollection(QObject *parent)
    : QObject(parent)
    , m_items { new QQmlObjectListModel<Room>(this) }
{
}

RoomCollection::~RoomCollection()
{
}

void RoomCollection::read(const QJsonObject &json)
{
    READ_COLLECTION_PROPERTY_IF_EXISTS(Room, json, jsonRoomsTag, items)
}

void RoomCollection::write(QJsonObject &json) const
{
    WRITE_COLLECTION_PROPERTY(json, jsonRoomsTag, items)
}

void RoomCollection::clearLocalData()
{
    m_items->clear();
}

void RoomCollection::appendNewRoom()
{
    Room* room = new Room();
    // TODO: give room an index
    m_items->append(room);
}

void RoomCollection::removeRoom(int index)
{
    qDebug() << "removing:" << index;
    m_items->remove(index);
}

} // namespace il
