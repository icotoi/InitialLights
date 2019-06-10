#pragma once

#include <QObject>
#include "QQmlAutoPropertyHelpers.h"
#include "QQmlEnumClassHelper.h"
#include "QQmlObjectListModel.h"

namespace il {

class LightControllerPWMChannel;

class AbstractLightController : public QObject
{
public:
    enum ControllerType {
        UndefinedControllerType,
        V1_4xPWM,
        V1_1xPWM_1xRGB,
        V1_2x10V,
    };
    Q_ENUM(ControllerType)

private:
    Q_OBJECT

    QML_READONLY_AUTO_PROPERTY(il::AbstractLightController::ControllerType, controllerType)
    QML_READONLY_AUTO_PROPERTY(QString, name)
    QML_READONLY_AUTO_PROPERTY(QString, address)

    QML_OBJMODEL_PROPERTY(il::LightControllerPWMChannel, pwmChannels)

public:
    explicit AbstractLightController(QObject *parent = nullptr);
    ~AbstractLightController();

public slots:
    virtual void connectToController() = 0;
    virtual void disconnectFromController() = 0;
};

} // namespace il
