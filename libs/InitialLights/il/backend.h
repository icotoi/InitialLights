#pragma once

#include "initiallights_global.h"
#include "QQmlAutoPropertyHelpers.h"
#include "QQmlObjectListModel.h"

namespace il {

class RoomCollection;
class User;

class INITIALLIGHTSSHARED_EXPORT BackEnd : public QObject
{
    Q_OBJECT

    QML_READONLY_AUTO_PROPERTY(int, version)

    QML_WRITABLE_AUTO_PROPERTY(bool, showOnboarding)
    QML_WRITABLE_AUTO_PROPERTY(bool, showInitialSetup)

    Q_PROPERTY(il::RoomCollection* rooms READ rooms CONSTANT)
    Q_PROPERTY(il::User* user READ user CONSTANT)

public:
    explicit BackEnd(QObject *parent = nullptr);
    ~BackEnd() override;

public slots:
    void clearLocalData();
    void loadLocalData();
    void saveLocalData();

    RoomCollection* rooms() const { return m_rooms; }
    User* user() const { return m_user; }

private:
    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;

    RoomCollection* m_rooms;
    User* m_user;
};

} // namespace il
