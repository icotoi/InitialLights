#include "idecodable.h"

namespace il {

IDecodable::~IDecodable()
{
}

void IDecodable::readIfExists(const QJsonObject &json, const QString &tag) {
    if (json.contains(tag) && json[tag].isObject()) {
        read(json[tag].toObject());
    }
}

void readIfExists(const QJsonObject &json, const QString &tag, bool &out) {
    if (json.contains(tag) && json[tag].isBool()) {
        out = json[tag].toBool();
    }
}

}
