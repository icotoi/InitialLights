#pragma once

#include "initiallights_global.h"

#include "QQmlAutoPropertyHelpers.h"

namespace il {

class ChannelBase : public QObject
{
    Q_OBJECT

    QML_CONSTANT_AUTO_PROPERTY(QString, name)
    QML_CONSTANT_AUTO_PROPERTY(QString, version)

    QML_CONSTANT_AUTO_PROPERTY(int, minValue)
    QML_CONSTANT_AUTO_PROPERTY(int, maxValue)
    QML_CONSTANT_AUTO_PROPERTY(int, valueIncrement)

public:
    virtual ~ChannelBase();

protected:
    explicit ChannelBase(const QString& name,
                             const QString& version,
                             int minValue,
                             int maxValue,
                             int valueIncrement,
                             QObject *parent = nullptr);
};

} // namespace il
