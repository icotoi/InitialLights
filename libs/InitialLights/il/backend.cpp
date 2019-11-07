#include "backend.h"

#include "controllercollection.h"
#include "jsonhelper.h"
#include "roomcollection.h"
#include "simpleindexer.h"
#include "user.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

namespace il {

namespace  {

const QString jsonShowOnboardingTag { "showOnboarding" };
const QString jsonShowInitialSetupTag { "showInitialSetup" };

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
    , m_showOnboarding { true }
    , m_showInitialSetup { true }
    , m_user { new User(this) }
{
    auto indexerAllocator = [](IIndexed* indexed, QObject* parent) { return new SimpleIndexer(indexed, parent); };
    m_controllers = new ControllerCollection(indexerAllocator, this);
    m_rooms = new RoomCollection(indexerAllocator, this);
}

BackEnd::~BackEnd()
{
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
    READ_PROPERTY_IF_EXISTS(bool, json, jsonShowOnboardingTag, showOnboarding)
    READ_PROPERTY_IF_EXISTS(bool, json, jsonShowInitialSetupTag, showInitialSetup)

    m_controllers->read(json);
    m_rooms->read(json);
    m_user->read(json);
}

void BackEnd::write(QJsonObject &json) const
{
    json[jsonShowOnboardingTag] = m_showOnboarding;
    json[jsonShowInitialSetupTag] = m_showInitialSetup;

    m_controllers->write(json);
    m_rooms->write(json);
    m_user->write(json);
}

void BackEnd::clearLocalData()
{
    qDebug() << "clearing local data...";

    set_showOnboarding(true);
    set_showInitialSetup(true);

    m_controllers->clearLocalData();
    m_rooms->clearLocalData();
    m_user->clearLocalData();

    QFile::remove(localDataFileName());
}

} // namespace il
