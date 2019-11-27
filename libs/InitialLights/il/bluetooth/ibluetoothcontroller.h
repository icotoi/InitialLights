#pragma once

#include "initiallights_global.h"
#include "QQmlVarPropertyHelpers.h"

#include <QBluetoothDeviceInfo>

namespace il {
namespace bluetooth {

class INITIALLIGHTSSHARED_EXPORT IBluetoothController : public QObject
{
    Q_OBJECT

    QML_READONLY_VAR_PROPERTY(bool, isConnected)
    QML_READONLY_VAR_PROPERTY(bool, isConnecting)
    QML_READONLY_VAR_PROPERTY(QString, message)

public:
    ~IBluetoothController() override;

    enum Light {
        Light1,
        Light2,
        Light3,
        Light4,
        };

    virtual void connectToController(const QBluetoothDeviceInfo& info) = 0;
    virtual void disconnectFromController() = 0;
    virtual void lightWriteWithoutResponse(Light light, const QByteArray& data) = 0;

protected:
    explicit IBluetoothController(QObject *parent = nullptr);
};

} // namespace bluetooth
} // namespace il
