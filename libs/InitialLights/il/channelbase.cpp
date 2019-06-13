#include "channelbase.h"

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

}

void ChannelBase::write(QJsonObject &json) const
{

}

} // namespace il
