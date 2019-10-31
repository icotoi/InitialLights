#pragma once

#include "iencodable.h"
#include "idecodable.h"

namespace il
{

class INITIALLIGHTSSHARED_EXPORT ICodable : public IEncodable, public IDecodable
{
public:
    virtual ~ICodable();
};

}
