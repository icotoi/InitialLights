#include "deviceinfo.h"

#if defined (Q_OS_MAC)
#include <QBluetoothUuid>
#else
#include <QBluetoothAddress>
#endif

#include <QDebug>

namespace il {

namespace  {
    QBluetoothUuid uuidService(QStringLiteral("6E400001-B5A3-F393-E0A9-E50E24DCCA9E"));
}

DeviceInfo::DeviceInfo(const QBluetoothDeviceInfo &info, QObject *parent)
    : QObject(parent)
    , m_name { info.name() }
    , m_address { address(info) }
    , m_info { info }
{
}

QString DeviceInfo::address(const QBluetoothDeviceInfo &info)
{
#if defined(Q_OS_MAC)
    // workaround for Core Bluetooth:
    return info.deviceUuid().toString();
#else
    return info.address().toString();
#endif
}

bool DeviceInfo::isValidDevice(const QBluetoothDeviceInfo &info)
{
    return info.serviceUuids().contains(uuidService);
}

bool DeviceInfo::isValidService(const QBluetoothUuid &uuid)
{
    return uuid == uuidService;
}

}
