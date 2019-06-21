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

public:
    explicit MainPage(RoomList* allRooms = nullptr, QObject *parent = nullptr);
    ~MainPage() override;

    void read(const QJsonObject &json) override;
    void write(QJsonObject &json) const override;

public slots:
    void turnLights(int index, bool on);

private:
    void onAllRoomsRowsChanged();

    RoomList* m_allRooms;
};

} // namespace il
