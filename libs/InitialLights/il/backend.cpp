#include "backend.h"

#include "room.h"
#include "controllerlist.h"

namespace il {

BackEnd::BackEnd(QObject *parent)
    : QObject(parent)
    , m_version { 1 }
    , m_controllerList { new ControllerList(this) }
    , m_rooms { new QQmlObjectListModel<Room>(this) }
{
}

} // namespace il
