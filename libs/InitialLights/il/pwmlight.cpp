#include "pwmlight.h"

#include "jsonhelpers.h"

#include <QJsonObject>
#include <QDebug>

namespace il {

namespace  {
const QString jsonValueTag { "value" };
}

PWMLight::PWMLight(const QString &name, QObject *parent)
    : LightBase (name, "v1", PWM, 0, 255, 1, parent)
    , m_value { 0 }
{
}

void PWMLight::read(const QJsonObject &json)
{
    LightBase::read(json);

    safeRead(json, jsonValueTag, [&](int v) {
        set_value(v);
    });
}

void PWMLight::write(QJsonObject &json) const
{
    LightBase::write(json);
    json[jsonValueTag] = m_value;
}

} // namespace il
