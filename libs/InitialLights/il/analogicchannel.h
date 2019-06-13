#pragma once

#include "channelbase.h"

namespace il {

class INITIALLIGHTSSHARED_EXPORT AnalogicChannel : public ChannelBase
{
    Q_OBJECT

    QML_WRITABLE_AUTO_PROPERTY(int, value)

public:
    explicit AnalogicChannel(const QString& name, QObject *parent = nullptr);
};

} // namespace il
