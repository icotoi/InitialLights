#pragma once

#include "lightbase.h"

namespace il {

namespace lights {

class INITIALLIGHTSSHARED_EXPORT RGBWLight : public LightBase
{
    Q_OBJECT
public:
    explicit RGBWLight(QObject *parent = nullptr);
    ~RGBWLight() override;
};

} // namespace lights
} // namespace il
