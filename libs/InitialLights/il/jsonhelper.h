#pragma once

#include "initiallights_global.h"
#include <QJsonObject>

namespace il {

void readIfExists(const QJsonObject& json, const QString& tag, bool& out);

}
