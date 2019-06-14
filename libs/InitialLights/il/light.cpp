#include "light.h"

#include "jsonhelpers.h"

#include <QJsonObject>
#include <QMetaEnum>

namespace il {

namespace  {
const QString jsonNameTag { "name" };
const QString jsonVersionTag { "version" };
const QString jsonLightTypeTag { "type" };
const QString jsonMinValueTag { "minValue" };
const QString jsonMaxValueTag { "maxValue" };
const QString jsonValueIncrementTag { "valueIncrementTag" };

const QString jsonValueTag { "value" };

const QString jsonRedValueTag { "redValue" };
const QString jsonGreenValueTag { "greenValue" };
const QString jsonBlueValueTag { "blueValue" };
}

Light::Light(QObject *parent)
    : QObject (parent)
    , m_lightType { UndefinedLightType }
    , m_minValue { 0 }
    , m_maxValue { 255 }
    , m_valueIncrement { 1 }
    , m_value { 0 }
    , m_redValue { 0 }
    , m_greenValue { 0 }
    , m_blueValue { 0 }
{
}

Light::Light(Light::LightType lightType, const QString &name, QObject *parent)
    : Light(parent)
{
    m_lightType = lightType;
    m_name = name;
}

Light::~Light()
{
}

void Light::read(const QJsonObject &json)
{
    safeRead(json, jsonLightTypeTag, [&](const QString& s) {
        int value = QMetaEnum::fromType<LightType>().keyToValue(s.toStdString().c_str());
        if (value >= 0) {
            LightType lt = LightType(value);
            update_lightType(lt);
        }
    });

    safeRead(json, jsonNameTag, [&](const QString& s) { set_name(s); });
    safeRead(json, jsonMinValueTag, [&](int v) { update_minValue(v); });
    safeRead(json, jsonMaxValueTag, [&](int v) { update_maxValue(v); });
    safeRead(json, jsonValueIncrementTag, [&](int v) { update_valueIncrement(v); });

    switch (m_lightType) {
    case PWM:
    case Analogic:
        safeRead(json, jsonValueTag, [&](int v) { set_value(v); });
        set_redValue(0);
        set_greenValue(0);
        set_blueValue(0);

        break;
    case RGB:
        set_value(0);
        safeRead(json, jsonRedValueTag, [&](int v) { set_redValue(v); });
        safeRead(json, jsonGreenValueTag, [&](int v) { set_greenValue(v); });
        safeRead(json, jsonBlueValueTag, [&](int v) { set_blueValue(v); });
        break;
    default:
        qWarning() << "reading unknown light type";
        break;
    }
}

void Light::write(QJsonObject &json) const
{
    json[jsonNameTag] = m_name;
    json[jsonLightTypeTag] = QMetaEnum::fromType<LightType>().valueToKey(m_lightType);
    json[jsonMinValueTag] = m_minValue;
    json[jsonMaxValueTag] = m_maxValue;
    json[jsonValueIncrementTag] = m_valueIncrement;

    switch (m_lightType) {
    case Analogic:
    case PWM:
        json[jsonValueTag] = m_value;
        break;
    case RGB:
        json[jsonRedValueTag] = m_redValue;
        json[jsonGreenValueTag] = m_greenValue;
        json[jsonBlueValueTag] = m_blueValue;
        break;
    default:
        qWarning() << "writing unknown light type";
        break;
    }
}

QString Light::lightTypeName() const
{
    return QMetaEnum::fromType<LightType>().valueToKey(m_lightType);
}

QObject *Light::controller() const
{
    return parent()
            ? parent()->parent()
            : nullptr;
}

} // namespace il
