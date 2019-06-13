#include "jsonhelpers.h"

#include <QJsonObject>

namespace il {

void safeRead(const QJsonObject &json, const QString &tag, std::function<void(const QString&)> functor)
{
    if (json.contains(tag) && json[tag].isString())
        functor(json[tag].toString());
}

void safeRead(const QJsonObject &json, const QString &tag, QString &output)
{
    if (json.contains(tag) && json[tag].isString())
        output = json[tag].toString();
}

void safeRead(const QJsonObject &json, const QString &tag, std::function<void(int)> functor)
{
    if (json.contains(tag) && json[tag].isString())
        functor(json[tag].toInt());
}

void safeRead(const QJsonObject &json, const QString &tag, int &output)
{
    if (json.contains(tag) && json[tag].isString())
        output = json[tag].toInt();
}

} // namespace il
