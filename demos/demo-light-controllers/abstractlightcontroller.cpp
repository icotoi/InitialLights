#include "abstractlightcontroller.h"
#include "lightcontrollerpwmchannel.h"
#include "lightcontrollerrgbchannel.h"
#include "lightcontrollervoltagechannel.h"

namespace il {

AbstractLightController::AbstractLightController(QObject *parent)
    : QObject(parent)
    , m_controllerType { UndefinedControllerType }
    , m_isBusy { false }
    , m_isConnected { false }
    , m_pwmChannels { new QQmlObjectListModel<LightControllerPWMChannel>(this) }
    , m_rgbChannels { new QQmlObjectListModel<LightControllerRGBChannel>(this) }
    , m_voltageChannels { new QQmlObjectListModel<LightControllerVoltageChannel>(this) }
{
}

AbstractLightController::~AbstractLightController()
{
    clear();
}

void AbstractLightController::clear()
{
    m_pwmChannels->clear();
    m_rgbChannels->clear();
    m_voltageChannels->clear();
}

} // namespace il
