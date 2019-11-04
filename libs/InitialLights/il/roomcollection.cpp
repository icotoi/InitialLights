#include "roomcollection.h"

#include "room.h"

#include <QDebug>

namespace il {

RoomCollection::RoomCollection(QObject *parent)
    : QObject(parent)
    , m_items { new QQmlObjectListModel<Room>(this) }
{
}

RoomCollection::~RoomCollection()
{
}

void RoomCollection::appendNewRoom()
{
    Room* room = new Room();
    m_items->append(room);
}

void RoomCollection::removeRoom(int index)
{
    qDebug() << "removing:" << index;
    m_items->remove(index);
}

} // namespace il
