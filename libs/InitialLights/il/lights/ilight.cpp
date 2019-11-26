#include "ilight.h"

namespace il {
namespace lights {

ILight::ILight(QObject* parent)
    : QObject(parent)
    , m_kind { LightKind::Unknown }
    , m_controller { nullptr }
{
}

ILight::~ILight()
{
}

} // namespace lights
} // namespace il
