#include "rgbchannel.h"

#include "jsonhelpers.h"

#include <QJsonObject>

namespace il {

namespace  {
const QString jsonRedValueTag { "redValue" };
const QString jsonGreenValueTag { "greenValue" };
const QString jsonBlueValueTag { "blueValue" };
}

RGBChannel::RGBChannel(const QString &name, QObject *parent)
    : ChannelBase (name, "v1", RGB, 0, 255, 1, parent)
    , m_redValue { 0 }
    , m_greenValue { 0 }
    , m_blueValue { 0 }
{
}

void RGBChannel::read(const QJsonObject &json)
{
    ChannelBase::read(json);
    safeRead(json, jsonRedValueTag, [&](int v) { set_redValue(v); });
    safeRead(json, jsonGreenValueTag, [&](int v) { set_greenValue(v); });
    safeRead(json, jsonBlueValueTag, [&](int v) { set_blueValue(v); });
}

void RGBChannel::write(QJsonObject &json) const
{
    ChannelBase::write(json);
    json[jsonRedValueTag] = m_redValue;
    json[jsonGreenValueTag] = m_greenValue;
    json[jsonBlueValueTag] = m_blueValue;
}

} // namespace il
