#include "controllerbase.h"
#include "light.h"

#include "jsonhelpers.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QMetaEnum>

namespace il {

namespace  {
const QString jsonNameTag { "name" };
const QString jsonAddressTag { "address" };
const QString jsonControllerTypeTag { "type" };
const QString jsonLightsTag { "lights" };
}

ControllerBase::ControllerBase(QObject *parent)
    : QObject(parent)
    , m_controllerType { UndefinedControllerType }
    , m_isBusy { false }
    , m_isConnected { false }
    , m_lights { new QQmlObjectListModel<Light>(this) }
{
}

ControllerBase::~ControllerBase()
{
    clear();
}

QByteArray ControllerBase::updateDeviceCommand() const
{
    QString command;

    switch (controllerType()) {
    case V1_2x10V:
    {
        Q_ASSERT(m_lights->size() == 2);
        Q_ASSERT(m_lights->at(0)->lightType() == Light::Analogic);
        Q_ASSERT(m_lights->at(1)->lightType() == Light::Analogic);

        command = QStringLiteral(u"US%1%2%3\n")
                .arg(m_lights->at(0)->value(), 2, 16, QChar('0'))
                .arg(m_lights->at(1)->value(), 2, 16, QChar('0'))
                .arg(2, 6, 16, QChar('0'))
                ;
        break;
    }
    case V1_4xPWM: {
        Q_ASSERT(m_lights->size() == 4);
        Q_ASSERT(m_lights->at(0)->lightType() == Light::PWM);
        Q_ASSERT(m_lights->at(1)->lightType() == Light::PWM);
        Q_ASSERT(m_lights->at(2)->lightType() == Light::PWM);
        Q_ASSERT(m_lights->at(3)->lightType() == Light::PWM);

        command = QString("US%1%2%3%4%5\n")
                .arg(m_lights->at(0)->value(), 2, 16, QChar('0'))
                .arg(m_lights->at(1)->value(), 2, 16, QChar('0'))
                .arg(m_lights->at(2)->value(), 2, 16, QChar('0'))
                .arg(m_lights->at(3)->value(), 2, 16, QChar('0'))
                .arg(3, 2, 16, QChar('0'));
        break;
    }
    case V1_1xPWM_1xRGB: {
        Q_ASSERT(m_lights->size() == 2);
        Q_ASSERT(m_lights->at(0)->lightType() == Light::PWM);
        Q_ASSERT(m_lights->at(1)->lightType() == Light::RGB);

        auto pwmLight = m_lights->at(0);
        auto rgbLight = m_lights->at(1);
        command = QString("US%1%2%3%4%5\n")
                .arg(pwmLight->value(), 2, 16, QChar('0'))
                .arg(rgbLight->redValue(), 2, 16, QChar('0'))
                .arg(rgbLight->greenValue(), 2, 16, QChar('0'))
                .arg(rgbLight->blueValue(), 2, 16, QChar('0'))
                .arg(1, 2, 16, QChar('0'));
        break;
    }
    default:
        qWarning() << "don't know how to save controller state for controller type:" << controllerType();
        break;
    }

    return command.toUpper().toUtf8();
}

void ControllerBase::clear()
{
    m_lights->clear();
}

void ControllerBase::read(const QJsonObject &json)
{
    safeRead(json, jsonNameTag, [&](const QString& s) { update_name(s); });
    safeRead(json, jsonAddressTag, [&](const QString& s) { update_address(s); });
    safeRead(json, jsonControllerTypeTag, [&](const QString& s) {
        int value = QMetaEnum::fromType<ControllerType>().keyToValue(s.toStdString().c_str());
        if (value >= 0) {
            ControllerType ct { ControllerType(value) };
            update_controllerType(ct);
        }
    });

    readModel(json, jsonLightsTag, m_lights);
}

void ControllerBase::write(QJsonObject &json) const
{
    json[jsonNameTag] = m_name;
    json[jsonAddressTag] = m_address;
    json[jsonControllerTypeTag] = QMetaEnum::fromType<ControllerType>().valueToKey(m_controllerType);

    writeModel(json, jsonLightsTag, m_lights);
}

} // namespace il
