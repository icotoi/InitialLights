#include "analogiclight.h"

namespace il {
namespace lights {

AnalogicLight::AnalogicLight(QObject *parent)
    : LightBase(parent)
{
    set_kind(LightKind::Analogic);
}

AnalogicLight::~AnalogicLight()
{
}

} // namespace lights
} // namespace il
