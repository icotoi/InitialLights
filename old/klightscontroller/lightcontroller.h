#pragma once

#include <QObject>
#include "qt-supermacros/QQmlAutoPropertyHelpers.h"

#include "deviceinfo.h"

namespace il {

class LightController : public QObject
{
    Q_OBJECT
    QML_CONSTANT_AUTO_PROPERTY(il::DeviceInfo*, info)

public:
    explicit LightController(DeviceInfo* info, QObject *parent = nullptr);
};

} // namespace il
