#pragma once

#include "initiallights_global.h"

class QJsonObject;

namespace il
{

class INITIALLIGHTSSHARED_EXPORT IDecodable
{
public:
    virtual ~IDecodable();
    virtual void read(const QJsonObject& json) = 0;
};

#define READ_DECODABLE_OBJECT(json, tag, decodable) \
    if (json.contains(tag) && json[tag].isObject()) { \
        decodable->read(json[tag].toObject()); \
    }

}
