#include "lightcontroller.h"
#include "deviceinfo.h"
#include "lightcontrollerpwmchannel.h"

namespace il {

LightController::LightController(DeviceInfo *info, QObject *parent)
    : QObject(parent)
    , m_info { info }
    , m_pwmChannels { new QQmlObjectListModel<LightControllerPWMChannel>(this) }
{
    m_info->setParent(this);
}

LightController::~LightController()
{
}

void LightController::connectToController()
{
    qDebug() << "connecting to controller" << info()->address() << "...";

    // just for safety
    m_pwmChannels->clear();

    // FIXME: add actual connection code
    for (int i = 0; i < 4; ++i) {
        m_pwmChannels->append(new LightControllerPWMChannel(QString::number(i+1), this));
    }
}

void LightController::disconnectFromController()
{
    m_pwmChannels->clear();
}

} // namespace il
