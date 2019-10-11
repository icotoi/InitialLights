#pragma once

#include "initiallights_global.h"

#include <QJsonObject>

class QJsonObject;

namespace il
{

class INITIALLIGHTSSHARED_EXPORT IEncodable
{
public:
    virtual ~IEncodable();
    virtual void write(QJsonObject& json) const = 0;

    void writeTo(QJsonObject& json, const QString& tag);
};

}
