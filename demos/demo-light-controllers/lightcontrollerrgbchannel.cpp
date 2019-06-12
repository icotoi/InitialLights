#include "lightcontrollerrgbchannel.h"

namespace il {

LightControllerRGBChannel::LightControllerRGBChannel(const QString &name, QObject *parent)
    : QObject (parent)
    , m_name { name }
    , m_version { "v1" }
    , m_minValue { 0 }
    , m_maxValue { 255 }
    , m_valueIncrement { 1 }
    , m_redValue { 0 }
    , m_greenValue { 0 }
    , m_blueValue { 0 }
{
}

} // namespace il
