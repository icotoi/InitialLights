#include "room.h"

#include <QJsonObject>

namespace il {

Room::Room(QObject *parent) : QObject(parent)
{

}

void Room::write(QJsonObject &json) const
{
    json["name"] = m_name;
}

} // namespace il
