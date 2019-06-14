#pragma once

#include "lightbase.h"

namespace il {

class INITIALLIGHTSSHARED_EXPORT RGBLight : public LightBase
{
    Q_OBJECT

    QML_WRITABLE_AUTO_PROPERTY(int, redValue)
    QML_WRITABLE_AUTO_PROPERTY(int, greenValue)
    QML_WRITABLE_AUTO_PROPERTY(int, blueValue)

public:
    explicit RGBLight(const QString& name = QString(), QObject* parent = nullptr);

    void read(const QJsonObject& json) override;
    void write(QJsonObject& json) const override;
};

} // namespace il
