#pragma once

#include "initiallights_global.h"

#include "QQmlAutoPropertyHelpers.h"
#include "QQmlEnumClassHelper.h"
#include "QQmlObjectListModel.h"

namespace il {

class PWMChannel;
class RGBChannel;
class AnalogicChannel;

class INITIALLIGHTSSHARED_EXPORT ControllerBase : public QObject
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

    QML_READONLY_AUTO_PROPERTY(il::ControllerBase::ControllerType, controllerType)
    QML_READONLY_AUTO_PROPERTY(QString, name)
    QML_READONLY_AUTO_PROPERTY(QString, address)

    QML_READONLY_AUTO_PROPERTY(bool, isBusy)
    QML_READONLY_AUTO_PROPERTY(bool, isConnected)
    QML_READONLY_AUTO_PROPERTY(QString, message)

    QML_OBJMODEL_PROPERTY(il::AnalogicChannel, analogicChannels)
    QML_OBJMODEL_PROPERTY(il::PWMChannel, pwmChannels)
    QML_OBJMODEL_PROPERTY(il::RGBChannel, rgbChannels)

public:
    ~ControllerBase();

    virtual void clear();
    virtual void read(const QJsonObject& json);
    virtual void write(QJsonObject& json) const;

public slots:
    virtual void connectToController() = 0;
    virtual void disconnectFromController() = 0;
    virtual QByteArray updateDeviceCommand() const;

protected:
    explicit ControllerBase(QObject *parent = nullptr);

    void clearChannels();
};

} // namespace il
