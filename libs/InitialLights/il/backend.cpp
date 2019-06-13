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
}

void BackEnd::loadLocalData()
{
    auto loadFileName = localDataFileName();

    qDebug() << "loading local data from:" << loadFileName;

    auto livingroom = new il::Room;
    livingroom->set_name("Livingroom");
    m_rooms->append(livingroom);

    auto bedroom = new il::Room;
    bedroom->set_name("Bedroom");
    m_rooms->append(bedroom);

    for (int i=0; i < 3; ++i) {
        auto scene = new il::Scene;
        scene->set_name(QStringLiteral("Scene %1").arg(i));
        m_scenes->append(scene);
    }
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

void BackEnd::write(QJsonObject &json) const
{
    QJsonObject controllerListObject;
    m_controllerList->write(controllerListObject);
    json["controllers"] = controllerListObject;

    QJsonArray roomArray;
    std::for_each (m_rooms->constBegin(), m_rooms->constEnd(), [&roomArray](const Room* room) {
        QJsonObject roomObject;
        room->write(roomObject);
        roomArray.append(roomObject);
    });
    json["rooms"] = roomArray;

    QJsonArray sceneArray;
    std::for_each (m_scenes->constBegin(), m_scenes->constEnd(), [&sceneArray](const Scene* scene) {
        QJsonObject sceneObject;
        scene->write(sceneObject);
        sceneArray.append(sceneObject);
    });
    json["scenes"] = sceneArray;
}

} // namespace il
