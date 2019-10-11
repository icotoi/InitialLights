#include "idecodable.h"

il::IDecodable::~IDecodable()
{
}

void il::readIfExists(const QJsonObject &json, const QString &tag, bool &out) {
    if (json.contains(tag) && json[tag].isBool()) {
        out = json[tag].toBool();
    }
}
