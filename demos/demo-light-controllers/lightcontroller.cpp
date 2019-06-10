#include "lightcontroller.h"
#include "deviceinfo.h"
#include "lightcontrollerpwmchannel.h"

namespace il {

LightController::LightController(DeviceInfo *info, QObject *parent)
    : AbstractLightController (parent)
    , m_info { info }
{
    if (m_info) {
        m_info->setParent(this);
        update_name(m_info->name());
        update_address(m_info->address());
    }
}

LightController::~LightController()
{
}

void LightController::connectToController()
{
    // just for safety
    get_pwmChannels()->clear();
}

void LightController::disconnectFromController()
{
    get_pwmChannels()->clear();
}

} // namespace il
