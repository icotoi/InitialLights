#pragma once

#include <QObject>
#include "QQmlAutoPropertyHelpers.h"
#include "QQmlObjectListModel.h"

namespace il {

class DeviceInfo;
class LightControllerPWMChannel;

class LightController : public QObject
{
    Q_OBJECT

    QML_CONSTANT_AUTO_PROPERTY(il::DeviceInfo*, info)
    QML_OBJMODEL_PROPERTY(il::LightControllerPWMChannel, pwmChannels)

public:
    explicit LightController(DeviceInfo* info, QObject *parent = nullptr);
    ~LightController();

    Q_INVOKABLE void connectToController();
    Q_INVOKABLE void disconnectFromController();
};

} // namespace il
