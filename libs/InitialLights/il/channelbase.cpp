#include "channelbase.h"

#include "jsonhelpers.h"

#include <QJsonObject>
#include <QMetaEnum>

namespace il {

namespace  {
const QString jsonNameTag { "name" };
const QString jsonVersionTag { "version" };
const QString jsonChannelTypeTag { "channelType" };
const QString jsonMinValueTag { "minValue" };
const QString jsonMaxValueTag { "maxValue" };
const QString jsonValueIncrementTag { "valueIncrementTag" };

}

ChannelBase::ChannelBase(const QString& name,
                         const QString& version,
                         ChannelType channelType,
                         int minValue,
                         int maxValue,
                         int valueIncrement,
                         QObject *parent)
    : QObject(parent)
    , m_name { name }
    , m_version { version }
    , m_channelType { channelType }
    , m_minValue { minValue }
    , m_maxValue { maxValue }
    , m_valueIncrement { valueIncrement }
{
}

ChannelBase::~ChannelBase()
{
}

void ChannelBase::read(const QJsonObject &json)
{
    safeRead(json, jsonNameTag, [&](const QString& s) { update_name(s); });
    safeRead(json, jsonVersionTag, [&](const QString& s) { update_version(s); });
    safeRead(json, jsonChannelTypeTag, [&](const QString& s) {
        int value = QMetaEnum::fromType<ChannelType>().keyToValue(s.toStdString().c_str());
        if (value >= 0) {
            ChannelType ct { ChannelType(value) };
            update_channelType(ct);
        }
    });
    safeRead(json, jsonMinValueTag, [&](int v) { update_minValue(v); });
    safeRead(json, jsonMaxValueTag, [&](int v) { update_maxValue(v); });
    safeRead(json, jsonValueIncrementTag, [&](int v) { update_valueIncrement(v); });
}

void ChannelBase::write(QJsonObject &json) const
{
    json[jsonNameTag] = m_name;
    json[jsonVersionTag] = m_version;
    json[jsonChannelTypeTag] = QMetaEnum::fromType<ChannelType>().valueToKey(m_channelType);
    json[jsonMinValueTag] = m_minValue;
    json[jsonMaxValueTag] = m_maxValue;
    json[jsonValueIncrementTag] = m_valueIncrement;
}

} // namespace il
