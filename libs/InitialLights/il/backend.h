#pragma once

#include "initiallights_global.h"
#include "QQmlAutoPropertyHelpers.h"
#include "QQmlObjectListModel.h"

namespace il {

class INITIALLIGHTSSHARED_EXPORT BackEnd : public QObject
{
    Q_OBJECT

    QML_READONLY_AUTO_PROPERTY(int, version)

    QML_WRITABLE_AUTO_PROPERTY(bool, showOnboarding)
    QML_WRITABLE_AUTO_PROPERTY(bool, isUserLogged)

public:
    explicit BackEnd(QObject *parent = nullptr);
    ~BackEnd() override;

public slots:
    void clearLocalData();
    void loadLocalData();
    void saveLocalData();

    void login(const QString& user, const QString& password);
    void resetPassword(const QString& user);
    void registerNewUser(const QString& user, const QString& password, const QString& fullName);
    void logout();

private:
    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;
};

} // namespace il
