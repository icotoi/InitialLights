#pragma once

#include "channelbase.h"

namespace il {

class INITIALLIGHTSSHARED_EXPORT PWMChannel : public ChannelBase
{
    Q_OBJECT

    QML_WRITABLE_AUTO_PROPERTY(int, value)

public:
    explicit PWMChannel(const QString& name, QObject *parent = nullptr);
};

} // namespace il
