#include "backend.h"

#include "controllerlist.h"
#include "room.h"
#include "scene.h"

namespace il {

BackEnd::BackEnd(QObject *parent)
    : QObject(parent)
    , m_version { 1 }
    , m_controllerList { new ControllerList(this) }
    , m_rooms { new QQmlObjectListModel<Room>(this) }
    , m_scenes { new QQmlObjectListModel<Scene>(this) }
{
}

void BackEnd::clearLocalData()
{
    qDebug() << "clearing local data...";
    m_rooms->clear();
    m_scenes->clear();
    m_controllerList->clear();
}

void BackEnd::loadLocalData()
{
    qDebug() << "loading local data...";

    auto livingroom = new il::Room;
    livingroom->set_name("Livingroom");
    m_rooms->append(livingroom);

    auto bedroom = new il::Room;
    bedroom->set_name("Bedroom");
    m_rooms->append(bedroom);

    for (int i=0; i < 3; ++i) {
        auto scene = new il::Scene;
        scene->set_name(QStringLiteral("Scene %1").arg(i));
        m_scenes->append(scene);
    }
}

void BackEnd::saveLocalData()
{
    qDebug() << "saving local data...";
}

} // namespace il
