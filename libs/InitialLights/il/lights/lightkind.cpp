#include "lightkind.h"

#include "../jsonhelper.h"

#include <QJsonObject>

namespace il {

namespace {
void readIfExists(const QJsonObject &json, const QString &tag, lights::LightKind::Kind &out)
{
    if (json.contains(tag) && json[tag].isString()) {
        int newValue = QMetaEnum::fromType<lights::LightKind::Kind>().keyToValue(json[tag].toString().toStdString().c_str());
        if (newValue >= 0) {
            out = lights::LightKind::Kind(newValue);
        }
    }
}
}

namespace lights {

const QString LightKind::jsonKindTag { "kind" };

LightKind::LightKind(QObject *parent)
    : QObject(parent)
{
}

LightKind::~LightKind()
{
}

LightKind::Kind LightKind::kind(const QJsonObject &json)
{
    Kind value = Unknown;
    readIfExists(json, jsonKindTag, value);
    return value;
}

}
}
