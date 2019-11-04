#pragma once

#include "initiallights_global.h"

class QJsonObject;

namespace il {

#define READ_PROPERTY_IF_EXISTS(type, json, tag, property) \
    { \
        type value = m_ ## property; \
        readIfExists(json, tag, value); \
        set_ ## property(value); \
        qDebug() << " >>> " #property " (" #type "):" << m_ ## property; \
    }

#define READ_COLLECTION_PROPERTY_IF_EXISTS(type, json, tag, property) \
    { \
        if (json.contains(tag) && json[tag].isArray()) { \
            QJsonArray jsonArray { json[tag].toArray() }; \
            m_ ## property->clear(); \
            for (int i = 0; i < jsonArray.size(); ++i) { \
                QJsonObject jsonObject = jsonArray[i].toObject(); \
                type* object = new type; \
                object->read(jsonObject); \
                m_ ## property->append(object); \
            } \
        } \
    }

#define WRITE_COLLECTION_PROPERTY(json, tag, property) \
    { \
        QJsonArray jsonArray; \
        for(int i = 0; i < m_ ## property->size(); ++i) { \
            auto object = m_ ## property->at(i); \
            QJsonObject jsonObject; \
            object->write(jsonObject); \
            jsonArray.append(jsonObject); \
        } \
        json[tag] = jsonArray; \
    }

void readIfExists(const QJsonObject& json, const QString& tag, bool& out);
void readIfExists(const QJsonObject& json, const QString& tag, int& out);
void readIfExists(const QJsonObject& json, const QString& tag, QString& out);

}
