#pragma once

#include "abstractchannel.h"

namespace il {

class INITIALLIGHTSSHARED_EXPORT RGBChannel : public AbstractChannel
{
    Q_OBJECT

    QML_WRITABLE_AUTO_PROPERTY(int, redValue)
    QML_WRITABLE_AUTO_PROPERTY(int, greenValue)
    QML_WRITABLE_AUTO_PROPERTY(int, blueValue)

public:
    explicit RGBChannel(const QString& name, QObject* parent = nullptr);
};

} // namespace il
