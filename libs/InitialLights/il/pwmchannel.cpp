#include "pwmchannel.h"

#include "jsonhelpers.h"

#include <QJsonObject>
#include <QDebug>

namespace il {

namespace  {
const QString jsonValueTag { "value" };
}

PWMChannel::PWMChannel(const QString &name, QObject *parent)
    : ChannelBase (name, "v1", PWM, 0, 255, 1, parent)
    , m_value { 0 }
{
}

void PWMChannel::read(const QJsonObject &json)
{
    ChannelBase::read(json);

    safeRead(json, jsonValueTag, [&](int v) {
        set_value(v);
    });
}

void PWMChannel::write(QJsonObject &json) const
{
    ChannelBase::write(json);
    json[jsonValueTag] = m_value;
}

} // namespace il
