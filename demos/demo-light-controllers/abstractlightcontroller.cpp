#include "abstractlightcontroller.h"
#include "lightcontrollerpwmchannel.h"
#include "lightcontrollerrgbchannel.h"
#include "lightcontrollervoltagechannel.h"

namespace il {

AbstractLightController::AbstractLightController(QObject *parent)
    : QObject(parent)
    , m_controllerType { UndefinedControllerType }
    , m_pwmChannels { new QQmlObjectListModel<LightControllerPWMChannel>(this) }
    , m_rgbChannels { new QQmlObjectListModel<LightControllerRGBChannel>(this) }
    , m_voltageChannels { new QQmlObjectListModel<LightControllerVoltageChannel>(this) }
{
}

AbstractLightController::~AbstractLightController()
{
}

} // namespace il
