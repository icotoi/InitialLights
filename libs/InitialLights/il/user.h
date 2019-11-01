#pragma once

#include "initiallights_global.h"
#include "QQmlAutoPropertyHelpers.h"
#include "QQmlObjectListModel.h"

namespace il {

class INITIALLIGHTSSHARED_EXPORT User : public QObject
{
    Q_OBJECT

    QML_WRITABLE_AUTO_PROPERTY(bool, isLogged)

public:
    explicit User(QObject *parent = nullptr);
    virtual ~User();

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;
    void clearLocalData();

public slots:
    QString validateEmail(QString email) const;
    QString validatePassword(QString password) const;

    void login(const QString& user, const QString& password);
    void resetPassword(const QString& user);
    void registerNewUser(const QString& user, const QString& password, const QString& fullName);
    void logout();
};

} // namespace il
