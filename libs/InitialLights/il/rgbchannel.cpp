#include "rgbchannel.h"

namespace il {

RGBChannel::RGBChannel(const QString &name, QObject *parent)
    : ChannelBase (name, "v1", 0, 255, 1, parent)
    , m_redValue { 0 }
    , m_greenValue { 0 }
    , m_blueValue { 0 }
{
}

} // namespace il
