#include "rgbwlight.h"
#include "../bluetooth/bluetoothcontroller.h"
#include "../controllers/controller.h"
#include "../jsonhelper.h"

#include <QJsonObject>

namespace il::lights {


namespace {

const QString jsonRedTag { "red" };
const QString jsonGreenTag { "green" };
const QString jsonBlueTag { "blue" };
const QString jsonWhiteTag { "white" };

bluetooth::BluetoothController::Light lightToControllerLight(RGBWLight::Light light)
{
    switch (light) {
    case il::lights::RGBWLight::Red:
        return bluetooth::BluetoothController::Light1;
        break;
    case il::lights::RGBWLight::Green:
        return bluetooth::BluetoothController::Light2;
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
    , m_red { 0 }
    , m_green { 0 }
    , m_blue { 0 }
    , m_white { 0 }
{
    set_kind(LightKind::RGBW);
}

RGBWLight::~RGBWLight()
{
}

void RGBWLight::read(const QJsonObject &json)
{
    LightBase::read(json);

    READ_PROPERTY_IF_EXISTS(int, json, jsonRedTag, red)
    READ_PROPERTY_IF_EXISTS(int, json, jsonGreenTag, green)
    READ_PROPERTY_IF_EXISTS(int, json, jsonBlueTag, blue)
    READ_PROPERTY_IF_EXISTS(int, json, jsonWhiteTag, white)
}

void RGBWLight::write(QJsonObject &json) const
{
    LightBase::write(json);

    json[jsonRedTag] = m_red;
    json[jsonGreenTag] = m_green;
    json[jsonBlueTag] = m_blue;
    json[jsonWhiteTag] = m_white;
}

void RGBWLight::set_red(int red)
{
    if (m_red == red)
        return;

    m_red = red;
    setValue(Red, m_red);
    emit redChanged(m_red);
}

void RGBWLight::set_green(int green)
{
    if (m_green == green)
        return;

    m_green = green;
    setValue(Green, m_green);
    emit greenChanged(m_green);
}

void RGBWLight::set_blue(int blue)
{
    if (m_blue == blue)
        return;

    m_blue = blue;
    setValue(Blue, m_blue);
    emit blueChanged(m_blue);
}

void RGBWLight::set_white(int white)
{
    if (m_white == white)
        return;

    m_white = white;
    setValue(White, m_white);
    emit whiteChanged(m_white);
}

void RGBWLight::setValue(Light light, int value) const
{
    if (!controller()) {
        qDebug() << "--- controller not set";
        return;
    }

    if (controller()->bluetoothController()) {
        qDebug() << "--- bluetooth controller not set";
        return;
    }

    QByteArray data(1, 0);
    data[0] = value;
    controller()->bluetoothController()->lightWriteWithoutResponse(lightToControllerLight(light), data);
}

} // namespace il::lights
