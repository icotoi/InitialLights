#include "dummylightcontroller.h"
#include "lightcontrollerpwmchannel.h"
#include "lightcontrollerrgbchannel.h"
#include "lightcontrollervoltagechannel.h"

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
    clear();

    switch (controllerType()) {
    case V1_4xPWM:
        for (int i = 0; i < 4; ++i) {
            get_pwmChannels()->append(new LightControllerPWMChannel(QString::number(i+1), this));
        }
        break;
    case V1_1xPWM_1xRGB:
        get_pwmChannels()->append(new LightControllerPWMChannel("1", this));
        get_rgbChannels()->append(new LightControllerRGBChannel("2", this));
        break;
    case V1_2x10V:
        for (int i = 0; i < 2; ++i) {
            get_voltageChannels()->append(new LightControllerVoltageChannel(QString::number(i+1), this));
        }
        break;
    default:
        break;
    }
}

void DummyLightController::disconnectFromController()
{
    clear();
}

void DummyLightController::clear()
{
    get_pwmChannels()->clear();
    get_rgbChannels()->clear();
    get_voltageChannels()->clear();
}

} // namespace il
