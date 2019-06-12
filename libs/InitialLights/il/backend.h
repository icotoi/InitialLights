#pragma once

#include "initiallights_global.h"

#include "QQmlAutoPropertyHelpers.h"
#include "QQmlObjectListModel.h"

namespace il {

class ControllerList;
class Room;

class INITIALLIGHTSSHARED_EXPORT BackEnd : public QObject
{
    Q_OBJECT

    QML_READONLY_AUTO_PROPERTY(int, version)
    QML_CONSTANT_AUTO_PROPERTY(il::ControllerList*, controllerList)
    QML_OBJMODEL_PROPERTY(Room, rooms)

public:
    explicit BackEnd(QObject *parent = nullptr);
};

} // namespace il
