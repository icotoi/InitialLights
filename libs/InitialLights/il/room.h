#pragma once

#include "initiallights_global.h"
#include "QQmlAutoPropertyHelpers.h"
#include "QQmlObjectListModel.h"

namespace il {

class INITIALLIGHTSSHARED_EXPORT Room : public QObject
{
    Q_OBJECT

    QML_WRITABLE_AUTO_PROPERTY(int, rid) // rid = room id (we can't use id or index)
    QML_WRITABLE_AUTO_PROPERTY(QString, name)

public:
    explicit Room(QObject *parent = nullptr);
    virtual ~Room();

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;
};

} // namespace il

