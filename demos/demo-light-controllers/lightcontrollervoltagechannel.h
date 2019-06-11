#pragma once

#include <QObject>

#include "QQmlAutoPropertyHelpers.h"

namespace il {

class LightControllerVoltageChannel : public QObject
{
    Q_OBJECT

    QML_CONSTANT_AUTO_PROPERTY(QString, name)
    QML_CONSTANT_AUTO_PROPERTY(QString, version)

    QML_CONSTANT_AUTO_PROPERTY(int, minValue)
    QML_CONSTANT_AUTO_PROPERTY(int, maxValue)
    QML_CONSTANT_AUTO_PROPERTY(int, valueIncrement)
    QML_WRITABLE_AUTO_PROPERTY(int, value)

public:
    explicit LightControllerVoltageChannel(const QString& name, QObject *parent = nullptr);
};

} // namespace il
