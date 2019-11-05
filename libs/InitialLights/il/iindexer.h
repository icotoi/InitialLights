#pragma once

#include "initiallights_global.h"

namespace il {

class INITIALLIGHTSSHARED_EXPORT IIndexer
{
public:
    virtual ~IIndexer();

    virtual int allocateNextFreeIndex() = 0;
    virtual void freeIndex(int index) = 0;

protected:
    IIndexer();
};

}
