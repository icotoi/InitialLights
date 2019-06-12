#pragma once

#include "abstractchannel.h"

namespace il {

class INITIALLIGHTSSHARED_EXPORT PWMChannel : public AbstractChannel
{
    Q_OBJECT

    QML_WRITABLE_AUTO_PROPERTY(int, value)

public:
    explicit PWMChannel(const QString& name, QObject *parent = nullptr);
};

} // namespace il
