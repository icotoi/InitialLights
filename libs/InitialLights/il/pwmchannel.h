#pragma once

#include "channelbase.h"

namespace il {

class INITIALLIGHTSSHARED_EXPORT PWMChannel : public ChannelBase
{
    Q_OBJECT

    QML_WRITABLE_AUTO_PROPERTY(int, value)

public:
    explicit PWMChannel(const QString& name = QString(), QObject *parent = nullptr);

    void read(const QJsonObject& json) override;
    void write(QJsonObject& json) const override;
};

} // namespace il
