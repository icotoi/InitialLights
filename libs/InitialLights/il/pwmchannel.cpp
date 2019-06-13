#include "pwmchannel.h"

namespace il {

PWMChannel::PWMChannel(const QString &name, QObject *parent)
    : ChannelBase (name, "v1", 0, 255, 1, parent)
    , m_value { 0 }
{
}

} // namespace il
