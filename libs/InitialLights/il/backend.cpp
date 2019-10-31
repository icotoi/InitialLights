#include "backend.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

namespace il {

namespace  {

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
    , m_showOnboarding { true }
    , m_isUserLogged { false }
{
}

BackEnd::~BackEnd()
{
}

void BackEnd::clearLocalData()
{
    qDebug() << "clearing local data...";
    set_showOnboarding(true);
    set_isUserLogged(false);

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

void BackEnd::logout()
{
    // TODO: do we need to notify the server about the logout?
    set_isUserLogged(false);
    qDebug() << ">>> Logout user";
}

void BackEnd::read(const QJsonObject &json)
{
    bool temporaryBool = m_showOnboarding;
    il::readIfExists(json, jsonShowOnboarding, temporaryBool);
    set_showOnboarding(temporaryBool);

    temporaryBool = m_isUserLogged;
    il::readIfExists(json, jsonIsUserLogged, temporaryBool);
    set_isUserLogged(temporaryBool);
}

void BackEnd::write(QJsonObject &json) const
{
    json[jsonShowOnboarding] = m_showOnboarding;
    json[jsonIsUserLogged] = m_isUserLogged;
}

} // namespace il
