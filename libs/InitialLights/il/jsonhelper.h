#pragma once

#include "initiallights_global.h"

#include "QQmlObjectListModel.h"
#include <QJsonArray>
#include <QJsonObject>

namespace il {

#define READ_PROPERTY_IF_EXISTS(type, json, tag, property) \
    { \
        type value = m_ ## property; \
        readIfExists(json, tag, value); \
        set_ ## property(value); \
        qDebug() << " >>> " #property " (" #type "):" << m_ ## property; \
    }

template<class T>
void readCollectionPropertyIfExists(const QJsonObject& json, const QString& tag, QQmlObjectListModel<T>* property)
{
    if (json.contains(tag) && json[tag].isArray()) {
        QJsonArray jsonArray = json[tag].toArray();
        property->clear();
        if (jsonArray.empty()) return;
        for (int i = 0; i < jsonArray.size(); ++i) {
            QJsonObject jsonObject = jsonArray[i].toObject();
            T* object = new T;
            object->read(jsonObject);
            property->append(object);
        }
    }
}

template<class T>
void writeCollectionProperty(QJsonObject& json, const QString& tag, const QQmlObjectListModel<T>* property)
{
    QJsonArray jsonArray;
    for(int i = 0; i < property->size(); ++i) {
        auto object = property->at(i);
        QJsonObject jsonObject;
        object->write(jsonObject);
        jsonArray.append(jsonObject);
    }
    json[tag] = jsonArray;
}

void readIfExists(const QJsonObject& json, const QString& tag, bool& out);
void readIfExists(const QJsonObject& json, const QString& tag, int& out);
void readIfExists(const QJsonObject& json, const QString& tag, QString& out);

}
