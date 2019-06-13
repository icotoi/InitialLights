#pragma once

#include "initiallights_global.h"

#include "QQmlAutoPropertyHelpers.h"
#include "QQmlEnumClassHelper.h"

namespace il {

class INITIALLIGHTSSHARED_EXPORT ChannelBase : public QObject
{
public:
    enum ChannelType {
        UndefinedChannelType,
        Analogic,
        PWM,
        RGB,
    };
    Q_ENUM(ChannelType)

private:
    Q_OBJECT

    QML_CONSTANT_AUTO_PROPERTY(QString, name)
    QML_CONSTANT_AUTO_PROPERTY(QString, version)
    QML_CONSTANT_AUTO_PROPERTY(il::ChannelBase::ChannelType, channelType)

    QML_CONSTANT_AUTO_PROPERTY(int, minValue)
    QML_CONSTANT_AUTO_PROPERTY(int, maxValue)
    QML_CONSTANT_AUTO_PROPERTY(int, valueIncrement)

public:
    virtual ~ChannelBase();

    virtual void read(const QJsonObject& json);
    virtual void write(QJsonObject& json) const;

protected:
    explicit ChannelBase(const QString& name,
                         const QString& version,
                         ChannelType channelType,
                         int minValue,
                         int maxValue,
                         int valueIncrement,
                         QObject *parent = nullptr);
};

} // namespace il
