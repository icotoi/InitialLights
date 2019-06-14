#include "controllerbase.h"
#include "pwmlight.h"
#include "rgblight.h"
#include "analogiclight.h"

#include "jsonhelpers.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QMetaEnum>

namespace il {

namespace  {
const QString jsonNameTag { "name" };
const QString jsonAddressTag { "address" };
const QString jsonControllerTypeTag { "type" };

const QString jsonAnalogicLightsTag { "analogicLights" };
const QString jsonPWMLightsTag { "pwmLights" };
const QString jsonRGBLightsTag { "rgbLights" };

template <typename T>
void writeLights(QJsonObject& json, const QString& tag, const T* lights) {
    QJsonArray lightArray;
    std::for_each (lights->constBegin(), lights->constEnd(), [&lightArray](const LightBase* light) {
        QJsonObject lightObject;
        light->write(lightObject);
        lightArray.append(lightObject);
    });
    json[tag] = lightArray;
}

template <typename T>
void readLights(const QJsonObject& json, const QString& tag, QQmlObjectListModel<T>* lights) {
    if (json.contains(tag) && json[tag].isArray()) {
        QJsonArray lightArray { json[tag].toArray() };
        lights->clear();
        for (int i = 0; i < lightArray.size(); ++i) {
            QJsonObject lightObject = lightArray[i].toObject();
            auto light = new T;
            light->read(lightObject);
            lights->append(light);
        }
    }
}
}

ControllerBase::ControllerBase(QObject *parent)
    : QObject(parent)
    , m_controllerType { UndefinedControllerType }
    , m_isBusy { false }
    , m_isConnected { false }
    , m_analogicLights { new QQmlObjectListModel<AnalogicLight>(this) }
    , m_pwmLights { new QQmlObjectListModel<PWMLight>(this) }
    , m_rgbLights { new QQmlObjectListModel<RGBLight>(this) }
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
        Q_ASSERT(m_analogicLights->size() == 2);
        Q_ASSERT(m_pwmLights->size() == 0);
        Q_ASSERT(m_rgbLights->size() == 0);

        auto lights = m_analogicLights;
        command = QStringLiteral(u"US%1%2%3\n")
                .arg(lights->at(0)->value(), 2, 16, QChar('0'))
                .arg(lights->at(1)->value(), 2, 16, QChar('0'))
                .arg(2, 6, 16, QChar('0'))
                ;
        break;
    }
    case V1_4xPWM: {
        Q_ASSERT(m_analogicLights->size() == 0);
        Q_ASSERT(m_pwmLights->size() == 4);
        Q_ASSERT(m_rgbLights->size() == 0);

        auto lights = m_pwmLights;
        command = QString("US%1%2%3%4%5\n")
                .arg(lights->at(0)->value(), 2, 16, QChar('0'))
                .arg(lights->at(1)->value(), 2, 16, QChar('0'))
                .arg(lights->at(2)->value(), 2, 16, QChar('0'))
                .arg(lights->at(3)->value(), 2, 16, QChar('0'))
                .arg(3, 2, 16, QChar('0'));
        break;
    }
    case V1_1xPWM_1xRGB: {
        Q_ASSERT(m_analogicLights->size() == 0);
        Q_ASSERT(m_pwmLights->size() == 1);
        Q_ASSERT(m_rgbLights->size() == 1);

        auto pwmLight = m_pwmLights->at(0);
        auto rgbLight = m_rgbLights->at(0);
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
    clearLights();
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

    readLights(json, jsonAnalogicLightsTag, m_analogicLights);
    readLights(json, jsonPWMLightsTag, m_pwmLights);
    readLights(json, jsonRGBLightsTag, m_rgbLights);
}

void ControllerBase::write(QJsonObject &json) const
{
    json[jsonNameTag] = m_name;
    json[jsonAddressTag] = m_address;
    json[jsonControllerTypeTag] = QMetaEnum::fromType<ControllerType>().valueToKey(m_controllerType);

    writeLights(json, jsonAnalogicLightsTag, m_analogicLights);
    writeLights(json, jsonPWMLightsTag, m_pwmLights);
    writeLights(json, jsonRGBLightsTag, m_rgbLights);
}

void ControllerBase::clearLights()
{
    m_analogicLights->clear();
    m_pwmLights->clear();
    m_rgbLights->clear();
}

} // namespace il
