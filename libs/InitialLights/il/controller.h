#pragma once

#include "initiallights_global.h"
#include "QQmlAutoPropertyHelpers.h"
#include "QQmlObjectListModel.h"

namespace il {

class INITIALLIGHTSSHARED_EXPORT Controller : public QObject
{
public:
    enum State: int {
        Unknown = 0,
        Offline,
        Unconfigured,
        Disabled,
        Enabled
    };

private:
    Q_OBJECT

    QML_WRITABLE_AUTO_PROPERTY(int, cid) // rid = room id (we can't use id or index)
    QML_WRITABLE_AUTO_PROPERTY(QString, name)
    QML_WRITABLE_AUTO_PROPERTY(QString, address)

    Q_ENUM(State)
    QML_WRITABLE_AUTO_PROPERTY(il::Controller::State, state)

public:
    explicit Controller(QObject *parent = nullptr);
    virtual ~Controller();

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;

private:
    void readStateIfExists(const QJsonObject& json);
};

} // namespace il
