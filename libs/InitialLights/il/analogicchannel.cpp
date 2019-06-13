#include "analogicchannel.h"

#include "jsonhelpers.h"

#include <QJsonObject>

namespace il {

namespace  {
const QString jsonValueTag { "value" };
}

AnalogicChannel::AnalogicChannel(const QString& name, QObject *parent)
    : ChannelBase (name, "v1", Analogic, 0, 255, 1, parent)
    , m_value { 0 }
{
}

void AnalogicChannel::read(const QJsonObject &json)
{
    ChannelBase::read(json);
    safeRead(json, jsonValueTag, [&](int v) { set_value(v); });
}

void AnalogicChannel::write(QJsonObject &json) const
{
    ChannelBase::write(json);
    json[jsonValueTag] = m_value;
}

} // namespace il
