#pragma once

#include "lightbase.h"

namespace il {

namespace lights {

class INITIALLIGHTSSHARED_EXPORT  AnalogicLight : public LightBase
{
    Q_OBJECT
public:
    explicit AnalogicLight(QObject *parent = nullptr);
    ~AnalogicLight() override;
};

} // namespace lights
} // namespace il
