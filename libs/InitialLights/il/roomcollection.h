#pragma once

#include <deque>

#include "initiallights_global.h"
#include "QQmlAutoPropertyHelpers.h"
#include "QQmlObjectListModel.h"

namespace il {

class Room;

class INITIALLIGHTSSHARED_EXPORT RoomCollection : public QObject
{
    Q_OBJECT

    QML_OBJMODEL_PROPERTY(il::Room, items)

public:
    explicit RoomCollection(QObject *parent = nullptr);
    virtual ~RoomCollection();

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;
    void clearLocalData();

public slots:
    void appendNewRoom();
    void removeRoom(int position);

private:
    int maxRoomIndex() const;
    int getNewRoomIndex();
    void freeRoomIndex(int index);
    std::deque<int> m_unusedRoomIndexes;
};

} // namespace il

