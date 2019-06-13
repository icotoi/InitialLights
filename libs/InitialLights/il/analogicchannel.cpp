#include "analogicchannel.h"

namespace il {

AnalogicChannel::AnalogicChannel(const QString& name, QObject *parent)
    : ChannelBase (name, "v1", Analogic, 0, 255, 1, parent)
    , m_value { 0 }
{
}

} // namespace il
