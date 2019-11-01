#include "jsonhelper.h"

namespace il {

void readIfExists(const QJsonObject &json, const QString &tag, bool &out)
{
    if (json.contains(tag) && json[tag].isBool()) {
        out = json[tag].toBool();
    }
}

}
