#pragma once

#include "initiallights_global.h"

#include "QQmlAutoPropertyHelpers.h"

namespace il {

class INITIALLIGHTSSHARED_EXPORT Room : public QObject
{
    Q_OBJECT

    QML_WRITABLE_AUTO_PROPERTY(QString, name)

public:
    explicit Room(QObject *parent = nullptr);

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;
};

} // namespace il
