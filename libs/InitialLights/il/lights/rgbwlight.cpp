#include "rgbwlight.h"
#include "../controllers/controller.h"
#include "../bluetooth/bluetoothcontroller.h"

namespace il::lights {


namespace {

bluetooth::BluetoothController::Light lightToControllerLight(RGBWLight::Light light)
{
    switch (light) {
    case il::lights::RGBWLight::Red:
        return bluetooth::BluetoothController::Light2;
        break;
    case il::lights::RGBWLight::Green:
        return bluetooth::BluetoothController::Light1;
        break;
    case il::lights::RGBWLight::Blue:
        return bluetooth::BluetoothController::Light3;
        break;
    case il::lights::RGBWLight::White:
        return bluetooth::BluetoothController::Light4;
        break;
    }
}

}


RGBWLight::RGBWLight(QObject *parent)
    : LightBase(parent)
{
    set_kind(LightKind::RGBW);
}

RGBWLight::~RGBWLight()
{
}

void RGBWLight::setRed(int red)
{
    if (m_red == red)
        return;

    m_red = red;
    setValue(Red, m_red);
    emit redChanged(m_red);
}

void RGBWLight::setGreen(int green)
{
    if (m_green == green)
        return;

    m_green = green;
    setValue(Green, m_green);
    emit greenChanged(m_green);
}

void RGBWLight::setBlue(int blue)
{
    if (m_blue == blue)
        return;

    m_blue = blue;
    setValue(Blue, m_blue);
    emit blueChanged(m_blue);
}

void RGBWLight::setWhite(int white)
{
    if (m_white == white)
        return;

    m_white = white;
    setValue(White, m_white);
    emit whiteChanged(m_white);
}

void RGBWLight::setValue(Light light, int value) const
{
    if (!controller() || !(controller()->bluetoothController())) {
        qDebug() << "--- controllers not set";
        return;
    }

    QByteArray data(1, 0);
    data[0] = value;
    controller()->bluetoothController()->lightWriteWithoutResponse(lightToControllerLight(light), data);
}

} // namespace il::lights
