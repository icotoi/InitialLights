#pragma once

#include "initiallights_global.h"

class QJsonObject;

namespace il
{

class INITIALLIGHTSSHARED_EXPORT IEncodable
{
public:
    virtual ~IEncodable();
    virtual void write(QJsonObject& json) const = 0;
};

#define WRITE_ENCODABLE_OBJECT(json, tag, encodable) \
    { \
        QJsonObject object; \
        encodable->write(object); \
        json[tag] = object; \
    }

}
