#include "lightbase.h"

#include "jsonhelpers.h"

#include "analogiclight.h"
#include "pwmlight.h"
#include "rgblight.h"

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
}

LightBase::LightBase(const QString& name,
                         const QString& version,
                         LightType lightType,
                         int minValue,
                         int maxValue,
                         int valueIncrement,
                         QObject *parent)
    : QObject(parent)
    , m_name { name }
    , m_version { version }
    , m_lightType { lightType }
    , m_minValue { minValue }
    , m_maxValue { maxValue }
    , m_valueIncrement { valueIncrement }
{
}

LightBase::~LightBase()
{
}

LightBase *LightBase::fromJson(const QJsonObject &json)
{
    LightBase* light;
    switch (readLightTypeFrom(json)) {
    case Analogic:
        light = new AnalogicLight;
        break;
    case PWM:
        light = new PWMLight;
        break;
    case RGB:
        light = new RGBLight;
        break;
    default:
        return nullptr;
    }

    light->read(json);

    return light;
}

void LightBase::read(const QJsonObject &json)
{
    safeRead(json, jsonNameTag, [&](const QString& s) { update_name(s); });
    safeRead(json, jsonVersionTag, [&](const QString& s) { update_version(s); });
    update_lightType(readLightTypeFrom(json));
    safeRead(json, jsonMinValueTag, [&](int v) { update_minValue(v); });
    safeRead(json, jsonMaxValueTag, [&](int v) { update_maxValue(v); });
    safeRead(json, jsonValueIncrementTag, [&](int v) { update_valueIncrement(v); });
}

void LightBase::write(QJsonObject &json) const
{
    json[jsonNameTag] = m_name;
    json[jsonVersionTag] = m_version;
    json[jsonLightTypeTag] = QMetaEnum::fromType<LightType>().valueToKey(m_lightType);
    json[jsonMinValueTag] = m_minValue;
    json[jsonMaxValueTag] = m_maxValue;
    json[jsonValueIncrementTag] = m_valueIncrement;
}

LightBase::LightType LightBase::readLightTypeFrom(const QJsonObject &json)
{
    LightType lt { UndefinedLightType};

    safeRead(json, jsonLightTypeTag, [&](const QString& s) {
        int value = QMetaEnum::fromType<LightType>().keyToValue(s.toStdString().c_str());
        if (value >= 0) {
            lt = LightType(value);
        }
    });

    return lt;
}

} // namespace il
