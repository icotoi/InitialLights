#include "user.h"

#include "jsonhelper.h"

#include <QDebug>
#include <QJsonObject>
#include <QRegularExpression>

namespace il {

namespace  {
const QString jsonUser { "user" };
const QString jsonIsLogged { "isLogged" };
}

User::User(QObject *parent)
    : QObject(parent)
    , m_isLogged(false)
{
}

User::~User()
{
}

void User::read(const QJsonObject &json)
{
    if (json.contains(jsonUser) && json[jsonUser].isObject()) {
        QJsonObject localJson = json[jsonUser].toObject();
        READ_BOOL_PROPERTY_IF_EXISTS(localJson, jsonIsLogged, isLogged)
    }
}

void User::write(QJsonObject &json) const
{
    QJsonObject localJson;
    localJson[jsonIsLogged] = m_isLogged;
    json[jsonUser] = localJson;
}

void User::clearLocalData()
{
    set_isLogged(false);
}

QString User::validateEmail(QString email) const
{
    if (email.isEmpty())
        return QString();

    QRegularExpression regexp("^[0-9A-Z]+(([0-9A-Z][-._+])*[0-9A-Z])*@[0-9A-Z]+([-.][0-9A-Z]+)*([0-9A-Z]*[.])[A-Z]{2,6}$",
                              QRegularExpression::CaseInsensitiveOption);
    return !regexp.match(email).hasMatch() ? tr("This is an invalid email address") : QString();
}

QString User::validatePassword(QString password) const
{
    // TODO: verify if this is enough for password check
    if (password.length() < 6)
        return tr("Password is too short");

    return QString();
}

void User::login(const QString &user, const QString &password)
{
    // TODO: implement login
    qDebug() << ">>> Login user";
    if (user == "xxx" && password == "xxx") {
        set_isLogged(true);
    } else {
        qDebug() << ">>> Invalid login request:"
                 << "\n   user:" << user
                 << "\n   password:" << password;
    }
}

void User::resetPassword(const QString &user)
{
    // TODO: implement password reset
    qDebug() << ">>> Requested password reset for user:" << user;
}

bool User::registerNewUser(const QString &user, const QString &password)
{
    // TODO: implement new user registration
    qDebug() << ">>> Requested new user registration for"
             << "\n   user:" << user
             << "\n   password:" << password;

    return true; // return false is registration fails
}

void User::logout()
{
    // TODO: do we need to notify the server about the logout?
    set_isLogged(false);
    qDebug() << ">>> Logout user";
}

} // namespace il
