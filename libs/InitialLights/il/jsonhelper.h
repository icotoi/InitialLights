#pragma once

#include "initiallights_global.h"
#include <QJsonObject>

namespace il {

#define READ_BOOL_PROPERTY_IF_EXISTS(json, name, property) \
    { \
        bool value = m_ ## property; \
        readIfExists(json, name, value); \
        set_ ## property(value); \
        qDebug() << " >>>" << #property << "(bool):" << m_ ## property; \
    }

void readIfExists(const QJsonObject& json, const QString& tag, bool& out);

}
