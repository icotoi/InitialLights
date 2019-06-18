#include "light.h"

#include "room.h"
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

const QString jsonSideXTag { "sideX" };
const QString jsonSideYTag { "sideY" };
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
    , m_sideX { 0.0 }
    , m_sideY { 0.0 }
    , m_room { nullptr }
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
    safeRead(json, jsonLightTypeTag, QJsonValue::String, [&](const QJsonValue& json) {
        int value = QMetaEnum::fromType<LightType>().keyToValue(json.toString().toStdString().c_str());
        if (value >= 0) {
            LightType lt = LightType(value);
            update_lightType(lt);
        }
    });

    safeRead(json, jsonNameTag, QJsonValue::String, [&](const QJsonValue& json) { set_name(json.toString()); });
    safeRead(json, jsonMinValueTag, QJsonValue::Double, [&](const QJsonValue& json) { update_minValue(json.toInt()); });
    safeRead(json, jsonMaxValueTag, QJsonValue::Double, [&](const QJsonValue& json) { update_maxValue(json.toInt()); });
    safeRead(json, jsonValueIncrementTag, QJsonValue::Double, [&](const QJsonValue& json) { update_valueIncrement(json.toInt()); });

    switch (m_lightType) {
    case PWM:
    case Analogic:
        safeRead(json, jsonValueTag, QJsonValue::Double, [&](const QJsonValue& json) { set_value(json.toInt()); });
        set_redValue(0);
        set_greenValue(0);
        set_blueValue(0);

        break;
    case RGB:
        set_value(0);
        safeRead(json, jsonRedValueTag, QJsonValue::Double, [&](const QJsonValue& json) { set_redValue(json.toInt()); });
        safeRead(json, jsonGreenValueTag, QJsonValue::Double, [&](const QJsonValue& json) { set_greenValue(json.toInt()); });
        safeRead(json, jsonBlueValueTag, QJsonValue::Double, [&](const QJsonValue& json) { set_blueValue(json.toInt()); });
        break;
    default:
        qWarning() << "reading unknown light type";
        break;
    }

    safeRead(json, jsonSideXTag, QJsonValue::Double, [&](const QJsonValue& json) { set_sideX(json.toDouble()); });
    safeRead(json, jsonSideYTag, QJsonValue::Double, [&](const QJsonValue& json) { set_sideY(json.toDouble()); });
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

    json[jsonSideXTag] = m_sideX;
    json[jsonSideYTag] = m_sideY;
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

void Light::setRoom(Room *room)
{
    if (m_room == room)
        return;

    if (m_room) {
        m_room->get_lights()->remove(this);
    }

    m_room = room;

    if (m_room) {
        auto lights = m_room->get_lights();
        if (lights) {
            if (!lights->contains(this)) {
                lights->append(this);
            } else {
                qWarning() << "room" << room->name() << "already has light" << m_name;
            }
        }
    } else {
        set_sideX(0);
        set_sideY(0);
    }

    emit roomChanged(m_room);
}

} // namespace il
