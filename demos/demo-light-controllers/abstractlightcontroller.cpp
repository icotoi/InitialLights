#include "abstractlightcontroller.h"
#include "lightcontrollerpwmchannel.h"

namespace il {

AbstractLightController::AbstractLightController(QObject *parent)
    : QObject(parent)
    , m_controllerType { UndefinedControllerType }
    , m_pwmChannels { new QQmlObjectListModel<LightControllerPWMChannel>(this) }
{
}

AbstractLightController::~AbstractLightController()
{
}

} // namespace il
