#include "mainpage.h"
#include "room.h"

#include <QDebug>
#include <QJsonDocument>

namespace il {

MainPage::MainPage(RoomList* allRooms, QObject *parent)
    : QObject(parent)
    , m_rooms { new RoomList(this) }
    , m_allRooms { allRooms }
{
    if (m_allRooms) {
        connect(m_allRooms, &RoomList::rowsInserted, this, &MainPage::onAllRoomsRowsChanged);
        connect(m_allRooms, &RoomList::rowsRemoved, this, &MainPage::onAllRoomsRowsChanged);
        connect(m_allRooms, &RoomList::rowsRemoved, this, &MainPage::onAllRoomsRowsChanged);
    }

    onAllRoomsRowsChanged();
}

MainPage::~MainPage()
{
}

void MainPage::read(const QJsonObject &/*json*/)
{
}

void MainPage::write(QJsonObject &/*json*/) const
{
}

void MainPage::turnLights(int index, bool on)
{
    if (index < 0 || index >= m_rooms->count()) {
        qWarning() << "invalid room index:" << index;
    }

    auto room = m_rooms->at(index);
    room->turnLights(on);
}

void MainPage::onAllRoomsRowsChanged()
{
    const int maxRoomsOnMainPage = 9;

    int index = 0;

    for (; index < std::min(maxRoomsOnMainPage, std::min(m_allRooms->count(), m_rooms->count())); ++index) {
        auto mainPageRoom = m_rooms->at(index);
        auto room = m_allRooms->at(index);
        if (mainPageRoom != room) {
            if (mainPageRoom) {
                m_rooms->remove(index);
            }
            m_rooms->insert(index, room);
        }
    }

    for (; index < std::min(maxRoomsOnMainPage, m_rooms->count()); ++index) {
        auto mainPageRoom = m_rooms->at(index);
        if (mainPageRoom) {
            m_rooms->remove(index);
        }
    }

    for (; index < std::min(maxRoomsOnMainPage, m_allRooms->count()); ++index) {
        auto room = m_allRooms->at(index);
        if (room) {
            m_rooms->insert(index, room);
        }
    }
}

} // namespace il
