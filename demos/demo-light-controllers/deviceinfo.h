#pragma once

#include <QObject>
#include <QBluetoothDeviceInfo>

#include "qt-supermacros/QQmlAutoPropertyHelpers.h"

namespace il {

class DeviceInfo: public QObject
{
    Q_OBJECT
    QML_READONLY_AUTO_PROPERTY(QString, name)
    QML_READONLY_AUTO_PROPERTY(QString, address)

public:
    explicit DeviceInfo(const QBluetoothDeviceInfo &device, QObject* parent = nullptr);

    static QString address(const QBluetoothDeviceInfo &device);

private:
    QBluetoothDeviceInfo m_device;
};

} // namespace il
