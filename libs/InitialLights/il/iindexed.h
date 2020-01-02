#pragma once

#include "initiallights_global.h"
#include <vector>

namespace il {

class INITIALLIGHTSSHARED_EXPORT IIndexed
{
public:
    virtual ~IIndexed();
    virtual int count() const = 0; // the current number of items
    virtual int maxIndex() const = 0; // the current maximum index
    virtual std::vector<int> indexes() const = 0; // get a list with current indexes

protected:
    IIndexed();
};

}
