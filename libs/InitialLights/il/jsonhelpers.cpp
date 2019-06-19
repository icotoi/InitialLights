#include "jsonhelpers.h"

namespace il {

void safeRead(const QJsonObject &json, const QString &tag, QJsonValue::Type jsonType, std::function<void (const QJsonValue &)> functor) {
    if (json.contains(tag) && json[tag].type() == jsonType)
        functor(json[tag]);
}

}
