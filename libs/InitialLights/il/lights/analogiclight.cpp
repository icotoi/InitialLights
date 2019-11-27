#include "analogiclight.h"
#include "../bluetooth/bluetoothcontroller.h"
#include "../controllers/controller.h"
#include "../jsonhelper.h"

#include <QJsonObject>

namespace il {

namespace {

const QString jsonChannelTag { "channel" };
const QString jsonValueTag { "value" };

bluetooth::BluetoothController::Light channelToControllerLight(lights::AnalogicLight::Channel channel)
{
    switch (channel) {
    case il::lights::AnalogicLight::Channel1:
        return bluetooth::BluetoothController::Light1;
        break;
    case il::lights::AnalogicLight::Channel2:
        return bluetooth::BluetoothController::Light2;
        break;
    }
}

void readIfExists(const QJsonObject &json, const QString &tag, lights::AnalogicLight::Channel &out)
{
    if (json.contains(tag) && json[tag].isString()) {
        int newValue = QMetaEnum::fromType<lights::AnalogicLight::Channel>().keyToValue(json[tag].toString().toStdString().c_str());
        if (newValue >= 0) {
            out = lights::AnalogicLight::Channel(newValue);
        }
    }
}

}

namespace lights {

AnalogicLight::AnalogicLight(QObject *parent)
    : LightBase(parent)
    , m_channel { Channel1 }
    , m_value { 0 }
{
    set_kind(LightKind::Analogic);
}

AnalogicLight::~AnalogicLight()
{
}

void AnalogicLight::read(const QJsonObject &json)
{
    LightBase::read(json);

    READ_PROPERTY_IF_EXISTS(int, json, jsonValueTag, value)
    READ_PROPERTY_IF_EXISTS(AnalogicLight::Channel, json, jsonChannelTag, channel)
}

void AnalogicLight::write(QJsonObject &json) const
{
    LightBase::write(json);

    json[jsonValueTag] = m_value;
    json[jsonChannelTag] = QMetaEnum::fromType<Channel>().valueToKey(m_channel);
}

void AnalogicLight::set_value(int value)
{
    if (m_value == value)
        return;

    m_value = value;
    setValue(m_channel, value);
    emit valueChanged(m_value);
}

void AnalogicLight::setValue(AnalogicLight::Channel channel, int value) const
{
    if (!controller() || !(controller()->bluetoothController())) {
        qDebug() << "--- controllers not set";
        return;
    }

    QByteArray data(1, 0);
    data[0] = value;
    controller()->bluetoothController()->lightWriteWithoutResponse(channelToControllerLight(channel), data);
}

} // namespace lights
} // namespace il
