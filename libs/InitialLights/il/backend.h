#pragma once

#include "initiallights_global.h"

#include "QQmlAutoPropertyHelpers.h"
#include "QQmlObjectListModel.h"

namespace il {

class ControllerList;
class Light;
class Room;
class Scene;

class INITIALLIGHTSSHARED_EXPORT BackEnd : public QObject
{
    Q_OBJECT

    QML_READONLY_AUTO_PROPERTY(int, version)
    QML_CONSTANT_AUTO_PROPERTY(il::ControllerList*, controllerList)
    QML_OBJMODEL_PROPERTY(il::Room, rooms)
    QML_OBJMODEL_PROPERTY(il::Scene, scenes)
    QML_OBJMODEL_PROPERTY(il::Light, lights)

public:
    explicit BackEnd(QObject *parent = nullptr);

public slots:
    void clearLocalData();
    void loadLocalData();
    void saveLocalData();

    void addNewRoom();

private:
    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;

    void onControllersInserted(const QModelIndex &parent, int first, int last);
    void onControllersAboutToBeRemoved(const QModelIndex &parent, int first, int last);

    void onLightsInserted(const QModelIndex &parent, int first, int last);
    void onLightsAboutToBeRemoved(const QModelIndex &parent, int first, int last);
};

} // namespace il
