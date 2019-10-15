#include "backend.h"

#include "controller.h"
#include "controllerlist.h"
#include "light.h"
#include "mainpage.h"
#include "room.h"
#include "scene.h"

#include "jsonhelpers.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

namespace il {

namespace  {

const QString jsonControllersTag { "controllers" };
const QString jsonRoomsTag { "rooms" };
const QString jsonScenesTag { "scenes" };
const QString jsonMainPageTag { "mainPage" };
const QString jsonShowOnboarding { "showOnboarding" };
const QString jsonIsUserLogged { "isUserLogged" };

QString localDataDirName()
{
    return QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
}

QString localDataFileName()
{
    return localDataDirName() + "/config.json";
}

bool createPathIfNeeded(const QString& path) {
    return QDir().mkpath(path);
}

}

BackEnd::BackEnd(QObject *parent)
    : QObject(parent)
    , m_version { 1 }
    , m_controllerList { new ControllerList(this) }
    , m_rooms { new QQmlObjectListModel<Room>(this) }
    , m_scenes { new QQmlObjectListModel<Scene>(this) }
    , m_lights { new QQmlObjectListModel<Light>(this) }
    , m_frontPageRooms { new QQmlObjectListModel<Room>(this) }
    , m_frontPageScenes { new QQmlObjectListModel<Scene>(this) }
    , m_showOnboarding { true }
    , m_isUserLogged { false }
    , m_mainPage { new MainPage(m_rooms, this) }
{
    auto controllers = m_controllerList->get_controllers();

    connect(controllers, &QAbstractListModel::rowsInserted, this, &BackEnd::onControllersInserted);
    connect(controllers, &QAbstractListModel::rowsAboutToBeRemoved, this, &BackEnd::onControllersAboutToBeRemoved);
}

BackEnd::~BackEnd()
{
}

void BackEnd::clearLocalData()
{
    qDebug() << "clearing local data...";
    m_rooms->clear();
    m_scenes->clear();
    m_controllerList->clear();
    set_showOnboarding(true);

    QFile::remove(localDataFileName());
}

void BackEnd::loadLocalData()
{
    auto loadFileName = localDataFileName();

    QFile loadFile(loadFileName);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Couldn't open save file:" << loadFile.fileName();

        loadFile.setFileName(":/DemoConfig.json");
        if(!loadFile.open(QIODevice::ReadOnly)) {
            qWarning() << "Couldn't open demo config file:" << loadFile.fileName();
            return;
        }
    }

    qDebug() << "loading local data from:" << loadFile.fileName();

    QByteArray saveData { loadFile.readAll() };
    QJsonDocument loadDoc { QJsonDocument::fromJson(saveData) };

    read(loadDoc.object());
}

void BackEnd::saveLocalData()
{
    createPathIfNeeded(localDataDirName());

    auto saveFileName = localDataFileName();

    QFile saveFile(saveFileName);
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning() << "Couldn't open save file:" << saveFileName;
        return;
    }

    qDebug() << "saving local data to:" << saveFileName;

    QJsonObject backendObject;
    write(backendObject);
    QJsonDocument saveDoc(backendObject);
    saveFile.write(saveDoc.toJson());
}

void BackEnd::addNewRoom()
{
    auto room = new Room(m_controllerList);
    room->set_name("Room");
    m_rooms->append(room);
}

void BackEnd::login(const QString &user, const QString &password)
{
    // TODO: implement login
    qDebug() << ">>> Login user";
    if (user == "xxx" && password == "xxx") {
        set_isUserLogged(true);
    } else {
        qDebug() << ">>> Invalid login request:"
                 << "\n   user:" << user
                 << "\n   password:" << password;
    }
}

void BackEnd::resetPassword(const QString &user)
{
    // TODO: implement password reset
    qDebug() << ">>> Requested password reset for user:" << user;
}

void BackEnd::registerNewUser(const QString &user, const QString &password, const QString &fullName)
{
    // TODO: implement new user registration
    qDebug() << ">>> Requested new user registration for"
             << "\n   user:" << user
             << "\n   password:" << password
             << "\n   name:" << fullName;
}

void BackEnd::read(const QJsonObject &json)
{
    bool temporaryBool = m_showOnboarding;
    il::readIfExists(json, jsonShowOnboarding, temporaryBool);
    set_showOnboarding(temporaryBool);

    temporaryBool = m_isUserLogged;
    il::readIfExists(json, jsonIsUserLogged, temporaryBool);
    set_isUserLogged(temporaryBool);

    m_controllerList->readIfExists(json, jsonControllersTag);

    if (json.contains(jsonRoomsTag) && json[jsonRoomsTag].isArray()) {
        QJsonArray roomArray { json[jsonRoomsTag].toArray() };
        m_rooms->clear();
        for (int i = 0; i < roomArray.size(); ++i) {
            QJsonObject roomObject = roomArray[i].toObject();
            auto room = new il::Room(m_controllerList);
            room->read(roomObject);
            m_rooms->append(room);
        }
    }

    if (json.contains(jsonScenesTag) && json[jsonScenesTag].isArray()) {
        QJsonArray scenesArray { json[jsonScenesTag].toArray() };
        m_scenes->clear();
        for (int i = 0; i < scenesArray.size(); ++i) {
            QJsonObject sceneObject { scenesArray[i].toObject() };
            auto scene = new il::Scene;
            scene->read(sceneObject);
            m_scenes->append(scene);
        }
    }

    m_mainPage->readIfExists(json, jsonMainPageTag);
}

void BackEnd::write(QJsonObject &json) const
{
    m_controllerList->writeTo(json, jsonControllersTag);
    m_controllerList->writeTo(json, jsonMainPageTag);

    QJsonArray roomArray;
    for (auto it = m_rooms->constBegin(); it != m_rooms->constEnd(); ++it) {
        auto room = *it;
        QJsonObject roomObject;
        room->write(roomObject);
        roomArray.append(roomObject);
    }
    json[jsonRoomsTag] = roomArray;

    QJsonArray sceneArray;
    for (auto it = m_scenes->constBegin(); it != m_scenes->constEnd(); ++it) {
        auto scene = *it;
        QJsonObject sceneObject;
        scene->write(sceneObject);
        sceneArray.append(sceneObject);
    }
    json[jsonScenesTag] = sceneArray;
    json[jsonShowOnboarding] = m_showOnboarding;
    json[jsonIsUserLogged] = m_isUserLogged;
}

void BackEnd::onControllersInserted(const QModelIndex &/*parent*/, int first, int last)
{
    auto controllers = m_controllerList->get_controllers();
    for (int index = first; index <= last; ++index) {
        auto controller = controllers->at(index);
        if (!controller) {
            qWarning() << "inserted NULL controller";
            return;
        }

        qDebug() << "inserted controller:" << controller->address()
                 << "with" << controller->get_lights()->count() << "lights";
        auto lights = controller->get_lights();
        for(auto it = lights->begin(); it != lights->end(); ++it) {
            auto light = *it;
            qDebug() << "inserted light:" << light->lightTypeName();
            m_lights->append(light);
        }

        connect(controller->get_lights(), &QAbstractListModel::rowsInserted, this, &BackEnd::onLightsInserted);
        connect(controller->get_lights(), &QAbstractListModel::rowsAboutToBeRemoved, this, &BackEnd::onLightsAboutToBeRemoved);
    }
}

void BackEnd::onControllersAboutToBeRemoved(const QModelIndex &/*parent*/, int first, int last)
{
    auto controllers = m_controllerList->get_controllers();
    for (int index = first; index <= last; ++index) {
        auto controller = controllers->at(index);
        if (!controller) {
            qWarning() << "removing NULL controller";
            return;
        }

        qDebug() << "removing:" << controller->address();

        auto lights = controller->get_lights();
        for(auto it = lights->begin(); it != lights->end(); ++it) {
            auto light = *it;
            qDebug() << "removing light:" << light->lightTypeName();
            m_lights->remove(light);
        }
    }
}

void BackEnd::onLightsInserted(const QModelIndex &/*parent*/, int first, int last)
{
    auto lights = qobject_cast<const QQmlObjectListModelBase*>(sender());
    if (!lights) {
        qWarning() << "trying to use invalid lights model on lights inserted";
        return;
    }

    for (int index = first; index <= last; ++index) {
        auto light = qobject_cast<Light*>(lights->get(index));
        if (!light) {
            qWarning() << "inserted NULL light";
            return;
        }

        qDebug() << "inserted light:" << light->lightTypeName();
        m_lights->append(light);
    }
}

void BackEnd::onLightsAboutToBeRemoved(const QModelIndex &/*parent*/, int first, int last)
{
    auto lights = qobject_cast<const QQmlObjectListModelBase*>(sender());
    if (!lights) {
        qWarning() << "trying to use invalid lights model on lights about to be removed";
        return;
    }

    for (int index = first; index <= last; ++index) {
        auto light = qobject_cast<Light*>(lights->get(index));
        if (!light) {
            qWarning() << "removing NULL light";
            return;
        }

        qDebug() << "removing light:" << light->lightTypeName();
        m_lights->remove(light);
    }
}

} // namespace il
