#include "backend.h"

#include "room.h"

namespace il {

BackEnd::BackEnd(QObject *parent)
    : QObject(parent)
    , m_version { 1 }
    , m_rooms { new QQmlObjectListModel<Room>(this) }
{
}

} // namespace il
