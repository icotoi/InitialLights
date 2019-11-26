#include "lightbase.h"

#include "../controllers/controller.h"
#include "../jsonhelper.h"

#include <QJsonObject>

namespace il {

namespace {
const QString jsonNameTag { "name" };
const QString jsonControllerTag { "controller" };
}

namespace lights {

LightBase::LightBase(QObject *parent)
    : ILight(parent)
{
}

LightBase::~LightBase()
{
}

void LightBase::read(const QJsonObject &json)
{
    READ_PROPERTY_IF_EXISTS(QString, json, jsonNameTag, name)
}

void LightBase::write(QJsonObject &json) const
{
    json[LightKind::jsonKindTag] = QMetaEnum::fromType<LightKind::Kind>().valueToKey(kind());
    json[jsonNameTag] = name();
}

} // namespace lights
} // namespace il
