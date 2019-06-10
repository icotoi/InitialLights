#include "lightcontrollerpwmchannel.h"

namespace il {

LightControllerPWMChannel::LightControllerPWMChannel(const QString &name, QObject *parent)
    : QObject(parent)
    , m_name { name }
    , m_version { "pwm.1" }
    , m_minValue { 0 }
    , m_maxValue { 31 }
    , m_valueIncrement { 1 }
    , m_value { 0 }
{
}

} // namespace il
