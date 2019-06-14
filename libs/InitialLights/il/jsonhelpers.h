#pragma once

#include <functional>

#include <QJsonArray>
#include <QJsonObject>

#include "QQmlObjectListModel.h"

namespace il {

void safeRead(const QJsonObject& json, const QString& tag, std::function<void(const QString&)> functor);
void safeRead(const QJsonObject& json, const QString& tag, std::function<void(int)> functor);

template <typename T>
void readModel(const QJsonObject& json, const QString& tag, QQmlObjectListModel<T>* model) {
    if (json.contains(tag) && json[tag].isArray()) {
        QJsonArray array { json[tag].toArray() };
        model->clear();
        for (int i = 0; i < array.size(); ++i) {
            QJsonObject object = array[i].toObject();
            auto item = T::fromJson(object);
            model->append(item);
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
} // namespace il
