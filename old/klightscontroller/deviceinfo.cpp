#include "deviceinfo.h"

#if defined (Q_OS_MAC)
#include <QBluetoothUuid>
#else
#include <QBluetoothAddress>
#endif

#include <QDebug>

namespace il {

DeviceInfo::DeviceInfo(const QBluetoothDeviceInfo &info, QObject *parent)
    : QObject(parent)
    , m_name { info.name() }
    , m_address { address(info) }
    , m_device { info }
{
}

DeviceInfo::~DeviceInfo()
{
//    qDebug() << "~DeviceInfo";
}

QString DeviceInfo::address(const QBluetoothDeviceInfo &device)
{
#if defined(Q_OS_MAC)
    // workaround for Core Bluetooth:
    return device.deviceUuid().toString();
#else
    return device.address().toString();
#endif
}

}
