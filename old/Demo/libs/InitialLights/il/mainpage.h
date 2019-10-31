#pragma once

#include "icodable.h"

#include "QQmlObjectListModel.h"

namespace il {

class Room;

class MainPage : public QObject, public ICodable
{
    typedef QQmlObjectListModel<Room> RoomList;

    Q_OBJECT

    QML_OBJMODEL_PROPERTY(il::Room, rooms)
    Q_PROPERTY(int sceneCount READ sceneCount CONSTANT)

public:
    explicit MainPage(RoomList* allRooms = nullptr, QObject *parent = nullptr);
    ~MainPage() override;

    void read(const QJsonObject &json) override;
    void write(QJsonObject &json) const override;

    int sceneCount() const { return SCENE_COUNT; }

public slots:
    void turnLights(int index, bool on);
    void turnAllLights(bool on);

private:
    void onAllRoomsRowsChanged();

    RoomList* m_allRooms;
};

} // namespace il
