#pragma once

#include "initiallights_global.h"
#include <QJsonObject>

namespace il
{

void readIfExists(const QJsonObject& json, const QString& tag, bool& out);

class INITIALLIGHTSSHARED_EXPORT IDecodable
{
public:
    virtual ~IDecodable();
    virtual void read(const QJsonObject& json) = 0;

    void readIfExists(const QJsonObject& json, const QString& tag) {
        if (json.contains(tag) && json[tag].isObject()) {
            read(json[tag].toObject());
        }
    }
};
}
