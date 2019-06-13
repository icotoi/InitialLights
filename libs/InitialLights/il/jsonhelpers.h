#pragma once

#include <functional>

class QJsonObject;
class QString;

namespace il {

void safeRead(const QJsonObject& json, const QString& tag, std::function<void(const QString&)> functor);
void safeRead(const QJsonObject& json, const QString& tag, QString& output);

void safeRead(const QJsonObject& json, const QString& tag, std::function<void(int)> functor);
void safeRead(const QJsonObject& json, const QString& tag, int& output);

} // namespace il
