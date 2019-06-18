#pragma once

#include <functional>

#include <QJsonArray>
#include <QJsonObject>

#include "QQmlObjectListModel.h"

namespace il {

void safeRead(const QJsonObject &json, const QString &tag, QJsonValue::Type jsonType, std::function<void(const QJsonValue &)> functor);

template <typename T>
void readModel(const QJsonObject& json, const QString& tag, QQmlObjectListModel<T>* model) {
    if (json.contains(tag) && json[tag].isArray()) {
        QJsonArray array { json[tag].toArray() };
        model->clear();
        for (int i = 0; i < array.size(); ++i) {
            QJsonObject object = array[i].toObject();
            auto item = new T;
            item->read(object);
            model->append(item);
        }
    }
}

template <typename T>
void readModel(const QJsonObject &json, const QString &tag, QQmlObjectListModel<T>* model, std::function<void (const QJsonObject &)> functor) {
    if (json.contains(tag) && json[tag].isArray()) {
        QJsonArray array { json[tag].toArray() };
        model->clear();
        for (int i = 0; i < array.size(); ++i) {
            QJsonObject object = array[i].toObject();
            functor(object);
        }
    }
}

template <typename T>
void writeModel(QJsonObject& json, const QString& tag, const QQmlObjectListModel<T>* model) {
    QJsonArray array;
    std::for_each (model->constBegin(), model->constEnd(), [&array](const T* item) {
        QJsonObject object;
        item->write(object);
        array.append(object);
    });
    json[tag] = array;
}

template <typename T>
void writeModel(QJsonObject& json, const QString& tag, const QQmlObjectListModel<T>* model, std::function<void(QJsonObject& json, const T*)> functor) {
    QJsonArray array;
    std::for_each (model->constBegin(), model->constEnd(), [&array, &functor](const T* item) {
        QJsonObject object;
        functor(object, item);
        array.append(object);
    });
    json[tag] = array;
}
} // namespace il
