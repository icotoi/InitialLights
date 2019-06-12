#include "abstractlightcontroller.h"
#include "lightcontrollerpwmchannel.h"
#include "lightcontrollerrgbchannel.h"
#include "lightcontrollervoltagechannel.h"

namespace il {

AbstractLightController::AbstractLightController(QObject *parent)
    : QObject(parent)
    , m_controllerType { UndefinedControllerType }
    , m_isBusy { false }
    , m_isConnected { false }
    , m_pwmChannels { new QQmlObjectListModel<LightControllerPWMChannel>(this) }
    , m_rgbChannels { new QQmlObjectListModel<LightControllerRGBChannel>(this) }
    , m_voltageChannels { new QQmlObjectListModel<LightControllerVoltageChannel>(this) }
{
}

AbstractLightController::~AbstractLightController()
{
    clear();
}

QByteArray AbstractLightController::updateDeviceCommand() const
{
    QString command;

    switch (controllerType()) {
    case V1_2x10V:
    {
        Q_ASSERT(get_voltageChannels()->size() == 2);
        Q_ASSERT(get_pwmChannels()->size() == 0);
        Q_ASSERT(get_rgbChannels()->size() == 0);

        auto channels = get_voltageChannels();
        command = QStringLiteral(u"US%1%2%3\n")
                .arg(channels->at(0)->value(), 2, 16, QChar('0'))
                .arg(channels->at(1)->value(), 2, 16, QChar('0'))
                .arg(2, 6, 16, QChar('0'))
                ;
        break;
    }
    case V1_4xPWM: {
        Q_ASSERT(get_voltageChannels()->size() == 0);
        Q_ASSERT(get_pwmChannels()->size() == 4);
        Q_ASSERT(get_rgbChannels()->size() == 0);

        auto channels = get_pwmChannels();
        command = QString("US%1%2%3%4%5\n")
                .arg(channels->at(0)->value(), 2, 16, QChar('0'))
                .arg(channels->at(1)->value(), 2, 16, QChar('0'))
                .arg(channels->at(2)->value(), 2, 16, QChar('0'))
                .arg(channels->at(3)->value(), 2, 16, QChar('0'))
                .arg(3, 2, 16, QChar('0'));
        break;
    }
    case V1_1xPWM_1xRGB: {
        Q_ASSERT(get_voltageChannels()->size() == 0);
        Q_ASSERT(get_pwmChannels()->size() == 1);
        Q_ASSERT(get_rgbChannels()->size() == 1);

        auto pwmChannel = get_pwmChannels()->at(0);
        auto rgbChannel = get_rgbChannels()->at(0);
        command = QString("US%1%2%3%4%5\n")
                .arg(pwmChannel->value(), 2, 16, QChar('0'))
                .arg(rgbChannel->redValue(), 2, 16, QChar('0'))
                .arg(rgbChannel->greenValue(), 2, 16, QChar('0'))
                .arg(rgbChannel->blueValue(), 2, 16, QChar('0'))
                .arg(1, 2, 16, QChar('0'));
        break;
    }
    default:
        qWarning() << "don't know how to save controller state for controller type:" << controllerType();
        break;
    }

    return command.toUpper().toUtf8();
}

void AbstractLightController::clear()
{
    clearChannels();
}

void AbstractLightController::clearChannels()
{
    m_pwmChannels->clear();
    m_rgbChannels->clear();
    m_voltageChannels->clear();
}

} // namespace il
