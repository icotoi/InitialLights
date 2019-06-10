#include "lightcontroller.h"

namespace il {

LightController::LightController(DeviceInfo *info, QObject *parent)
    : QObject(parent)
    , m_info { info }
{
    m_info->setParent(this);
}

} // namespace il
