#include "abstractchannel.h"

namespace il {

AbstractChannel::AbstractChannel(const QString& name,
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

AbstractChannel::~AbstractChannel()
{
}

} // namespace il
