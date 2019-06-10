#pragma once

#include <QObject>
#include <QBluetoothDeviceInfo>

#include "QQmlAutoPropertyHelpers.h"

namespace il {

class DeviceInfo: public QObject
{
    Q_OBJECT
    QML_READONLY_AUTO_PROPERTY(QString, name)
    QML_READONLY_AUTO_PROPERTY(QString, address)

public:
    explicit DeviceInfo(const QBluetoothDeviceInfo &info, QObject* parent = nullptr);

    static QString address(const QBluetoothDeviceInfo &info);
    static bool isValidDevice(const QBluetoothDeviceInfo &info);
    static bool isValidService(const QBluetoothUuid& uuid);

    const QBluetoothDeviceInfo& info() const { return m_info; }

private:
    QBluetoothDeviceInfo m_info;
};

} // namespace il
