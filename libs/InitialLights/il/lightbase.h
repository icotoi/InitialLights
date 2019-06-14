#pragma once

#include "initiallights_global.h"

#include "QQmlAutoPropertyHelpers.h"

namespace il {

class INITIALLIGHTSSHARED_EXPORT LightBase : public QObject
{
public:
    enum LightType {
        UndefinedLightType,
        Analogic,
        PWM,
        RGB,
    };
    Q_ENUM(LightType)

private:
    Q_OBJECT

    QML_READONLY_AUTO_PROPERTY(QString, name)
    QML_READONLY_AUTO_PROPERTY(QString, version)
    QML_READONLY_AUTO_PROPERTY(il::LightBase::LightType, lightType)

    QML_READONLY_AUTO_PROPERTY(int, minValue)
    QML_READONLY_AUTO_PROPERTY(int, maxValue)
    QML_READONLY_AUTO_PROPERTY(int, valueIncrement)

public:
    virtual ~LightBase();

    virtual void read(const QJsonObject& json);
    virtual void write(QJsonObject& json) const;

protected:
    explicit LightBase(const QString& name,
                         const QString& version,
                         LightType lightType,
                         int minValue,
                         int maxValue,
                         int valueIncrement,
                         QObject *parent = nullptr);
};

} // namespace il
