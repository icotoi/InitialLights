#include "jsonhelper.h"

namespace il {

void readIfExists(const QJsonObject &json, const QString &tag, bool &out)
{
    if (json.contains(tag) && json[tag].isBool()) {
        out = json[tag].toBool();
    }
}

void readIfExists(const QJsonObject &json, const QString &tag, int &out)
{
    if (json.contains(tag) && json[tag].isDouble()) {
        out = json[tag].toInt();
    }
}

void readIfExists(const QJsonObject &json, const QString &tag, QString &out)
{
    if (json.contains(tag) && json[tag].isString()) {
        out = json[tag].toString();
    }
}

}
