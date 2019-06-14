#pragma once

#include "lightbase.h"

namespace il {

class INITIALLIGHTSSHARED_EXPORT PWMLight : public LightBase
{
    Q_OBJECT

    QML_WRITABLE_AUTO_PROPERTY(int, value)

public:
    explicit PWMLight(const QString& name = QString(), QObject *parent = nullptr);

    void read(const QJsonObject& json) override;
    void write(QJsonObject& json) const override;
};

} // namespace il
