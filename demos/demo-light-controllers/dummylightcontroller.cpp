#include "dummylightcontroller.h"
#include "lightcontrollerpwmchannel.h"

namespace il {

DummyLightController::DummyLightController(ControllerType controllerType,
                                           const QString &name,
                                           const QString &address,
                                           QObject *parent)
    : AbstractLightController (parent)
{
    update_controllerType(controllerType);
    update_name(name);
    update_address(address);
}

void DummyLightController::connectToController()
{
    get_pwmChannels()->clear();

    switch (controllerType()) {
    case V1_4xPWM:
        for (int i = 0; i < 4; ++i) {
            get_pwmChannels()->append(new LightControllerPWMChannel(QString::number(i+1), this));
        }
        break;
    case V1_1xPWM_1xRGB:
        get_pwmChannels()->append(new LightControllerPWMChannel("1", this));
        break;
    case V1_2x10V:
        break;
    default:
        break;
    }
}

void DummyLightController::disconnectFromController()
{
    get_pwmChannels()->clear();
}

} // namespace il
