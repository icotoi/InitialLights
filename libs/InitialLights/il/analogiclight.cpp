#include "analogiclight.h"

#include "jsonhelpers.h"

#include <QJsonObject>

namespace il {

namespace  {
const QString jsonValueTag { "value" };
}

AnalogicLight::AnalogicLight(const QString& name, QObject *parent)
    : LightBase (name, "v1", Analogic, 0, 255, 1, parent)
    , m_value { 0 }
{
}

void AnalogicLight::read(const QJsonObject &json)
{
    LightBase::read(json);
    safeRead(json, jsonValueTag, [&](int v) { set_value(v); });
}

void AnalogicLight::write(QJsonObject &json) const
{
    LightBase::write(json);
    json[jsonValueTag] = m_value;
}

} // namespace il
