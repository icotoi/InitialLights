#include "channelbase.h"

namespace il {

ChannelBase::ChannelBase(const QString& name,
                                 const QString& version,
                                 int minValue,
                                 int maxValue,
                                 int valueIncrement,
                                 QObject *parent)
    : QObject(parent)
    , m_name { name }
    , m_version { version }
    , m_minValue { minValue }
    , m_maxValue { maxValue }
    , m_valueIncrement { valueIncrement }
{
}

ChannelBase::~ChannelBase()
{
}

} // namespace il
