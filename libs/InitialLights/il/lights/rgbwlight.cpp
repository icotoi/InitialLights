#include "rgbwlight.h"

namespace il::lights {

RGBWLight::RGBWLight(QObject *parent)
    : LightBase(parent)
{
    set_kind(LightKind::RGBW);
}

RGBWLight::~RGBWLight()
{
}

} // namespace il::lights
