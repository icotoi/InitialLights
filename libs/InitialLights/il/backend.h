#pragma once

#include "icodable.h"

#include "QQmlAutoPropertyHelpers.h"
#include "QQmlObjectListModel.h"

namespace il {

class ControllerList;
class Light;
class MainPage;
class Room;
class Scene;

class INITIALLIGHTSSHARED_EXPORT BackEnd : public QObject, public ICodable
{
    Q_OBJECT

    QML_READONLY_AUTO_PROPERTY(int, version)
    QML_CONSTANT_AUTO_PROPERTY(il::ControllerList*, controllerList)
    QML_OBJMODEL_PROPERTY(il::Room, rooms)
    QML_OBJMODEL_PROPERTY(il::Scene, scenes)
    QML_OBJMODEL_PROPERTY(il::Light, lights)

    QML_OBJMODEL_PROPERTY(il::Room, frontPageRooms)
    QML_OBJMODEL_PROPERTY(il::Scene, frontPageScenes)

    QML_WRITABLE_AUTO_PROPERTY(bool, showOnboarding)
    QML_WRITABLE_AUTO_PROPERTY(bool, isUserLogged)

    Q_PROPERTY(il::MainPage* mainPage READ mainPage CONSTANT)

public:
    explicit BackEnd(QObject *parent = nullptr);
    ~BackEnd() override;

    MainPage* mainPage() const { return m_mainPage; }

public slots:
    void clearLocalData();
    void loadLocalData();
    void saveLocalData();

    void addNewRoom();

    void login(const QString& user, const QString& password);
    void resetPassword(const QString& user);
    void registerNewUser(const QString& user, const QString& password, const QString& fullName);

private:
    void read(const QJsonObject& json) override;
    void write(QJsonObject& json) const override;

    void onControllersInserted(const QModelIndex &parent, int first, int last);
    void onControllersAboutToBeRemoved(const QModelIndex &parent, int first, int last);

    void onLightsInserted(const QModelIndex &parent, int first, int last);
    void onLightsAboutToBeRemoved(const QModelIndex &parent, int first, int last);
    MainPage* m_mainPage;
};

} // namespace il
