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
    room->set_rid(getNewRoomIndex());
    m_items->append(room);
}

void RoomCollection::removeRoom(int position)
{
    auto room = m_items->at(position);
    int rid = room->rid();
    m_items->remove(position);
//    qDebug() << "removing:" << position << "index:" << rid;
    freeRoomIndex(rid);
}

int RoomCollection::maxRoomIndex() const
{
    auto mi = std::max_element(m_items->begin(), m_items->end(), [](auto lhs, auto rhs) { return lhs->rid() < rhs->rid(); });
    return (*mi)->rid();
}

int RoomCollection::getNewRoomIndex()
{
    if (m_unusedRoomIndexes.empty()) {
        return m_items->count();
    } else {
        int index = m_unusedRoomIndexes.front();
        m_unusedRoomIndexes.pop_front();
        return index;
    }
}

void RoomCollection::freeRoomIndex(int index)
{
    m_unusedRoomIndexes.push_back(index);
    m_unusedRoomIndexes.erase(
        std::remove_if(m_unusedRoomIndexes.begin(), m_unusedRoomIndexes.end(), [this](int i) { return i >= std::max(m_items->count(), maxRoomIndex()); }),
        m_unusedRoomIndexes.end()
        );
    std::sort(m_unusedRoomIndexes.begin(), m_unusedRoomIndexes.end());
//    qDebug() << "unused room indexes:" << QList<int>::fromStdList(std::list<int>(m_unusedRoomIndexes.begin(), m_unusedRoomIndexes.end()));
}

} // namespace il
