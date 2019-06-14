#include "backend.h"

#include "controllerlist.h"
#include "room.h"
#include "scene.h"

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
{
}

void BackEnd::clearLocalData()
{
    qDebug() << "clearing local data...";
    m_rooms->clear();
    m_scenes->clear();
    m_controllerList->clear();

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

void BackEnd::read(const QJsonObject &json)
{
    if (json.contains(jsonControllersTag) && json[jsonControllersTag].isObject())
        m_controllerList->read(json[jsonControllersTag].toObject());

    if (json.contains(jsonRoomsTag) && json[jsonRoomsTag].isArray()) {
        QJsonArray roomArray { json[jsonRoomsTag].toArray() };
        m_rooms->clear();
        for (int i = 0; i < roomArray.size(); ++i) {
            QJsonObject roomObject = roomArray[i].toObject();
            auto room = new il::Room;
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
}

void BackEnd::write(QJsonObject &json) const
{
    QJsonObject controllerListObject;
    m_controllerList->write(controllerListObject);
    json[jsonControllersTag] = controllerListObject;

    QJsonArray roomArray;
    std::for_each (m_rooms->constBegin(), m_rooms->constEnd(), [&roomArray](const Room* room) {
        QJsonObject roomObject;
        room->write(roomObject);
        roomArray.append(roomObject);
    });
    json[jsonRoomsTag] = roomArray;

    QJsonArray sceneArray;
    std::for_each (m_scenes->constBegin(), m_scenes->constEnd(), [&sceneArray](const Scene* scene) {
        QJsonObject sceneObject;
        scene->write(sceneObject);
        sceneArray.append(sceneObject);
    });
    json[jsonScenesTag] = sceneArray;
}

} // namespace il
