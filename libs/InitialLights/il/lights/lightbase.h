#pragma once

#include "ilight.h"
#include "QQmlAutoPropertyHelpers.h"

namespace il {

class Controller;

namespace lights {

class INITIALLIGHTSSHARED_EXPORT  LightBase : public ILight
{
private:
    Q_OBJECT

public:
    virtual ~LightBase();

    void read(const QJsonObject& json) override;
    void write(QJsonObject& json) const override;

protected:
    explicit LightBase(QObject *parent = nullptr);
};

} // namespace lights
} // namespace il
