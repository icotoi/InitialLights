#pragma once

#include "initiallights_global.h"
#include "QQmlAutoPropertyHelpers.h"
#include "QQmlObjectListModel.h"

namespace il {

class INITIALLIGHTSSHARED_EXPORT Controller : public QObject
{
    Q_OBJECT

    QML_WRITABLE_AUTO_PROPERTY(int, cid) // rid = room id (we can't use id or index)
    QML_WRITABLE_AUTO_PROPERTY(QString, name)
    QML_WRITABLE_AUTO_PROPERTY(QString, address)

public:
    explicit Controller(QObject *parent = nullptr);
    virtual ~Controller();

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;
};

} // namespace il
