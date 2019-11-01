#pragma once

#include <QObject>

#include "QQmlAutoPropertyHelpers.h"

namespace il {

class LightControllerPWMChannel : public QObject
{
    Q_OBJECT

    QML_CONSTANT_AUTO_PROPERTY(QString, name)
    QML_CONSTANT_AUTO_PROPERTY(QString, version)

    QML_CONSTANT_AUTO_PROPERTY(int, minValue)
    QML_CONSTANT_AUTO_PROPERTY(int, maxValue)
    QML_CONSTANT_AUTO_PROPERTY(int, valueIncrement)
    QML_WRITABLE_AUTO_PROPERTY(int, value)

public:
    explicit LightControllerPWMChannel(const QString& name, QObject *parent = nullptr);
};

} // namespace il
