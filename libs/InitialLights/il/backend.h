#pragma once

#include "initiallights_global.h"

#include "QQmlAutoPropertyHelpers.h"
#include "QQmlObjectListModel.h"

namespace il {

class ControllerList;
class Room;
class Scene;

class INITIALLIGHTSSHARED_EXPORT BackEnd : public QObject
{
    Q_OBJECT

    QML_READONLY_AUTO_PROPERTY(int, version)
    QML_CONSTANT_AUTO_PROPERTY(il::ControllerList*, controllerList)
    QML_OBJMODEL_PROPERTY(il::Room, rooms)
    QML_OBJMODEL_PROPERTY(il::Scene, scenes)

public:
    explicit BackEnd(QObject *parent = nullptr);

public slots:
    void clearLocalData();
    void loadLocalData();
    void saveLocalData();

private:
    void write(QJsonObject& json) const;
};

} // namespace il
