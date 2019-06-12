#include "pwmchannel.h"

namespace il {

PWMChannel::PWMChannel(const QString &name, QObject *parent)
    : AbstractChannel (name, "v1", 0, 255, 1, parent)
    , m_value { 0 }
{
}

} // namespace il
