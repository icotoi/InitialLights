#include "jsonhelpers.h"

#include <QJsonObject>
#include <QDebug>

namespace il {

void safeRead(const QJsonObject &json, const QString &tag, std::function<void(const QString&)> functor)
{
    if (json.contains(tag) && json[tag].isString())
        functor(json[tag].toString());
}

void safeRead(const QJsonObject &json, const QString &tag, std::function<void(int)> functor)
{
    if (json.contains(tag) && json[tag].isDouble())
        functor(json[tag].toInt());
}

} // namespace il
