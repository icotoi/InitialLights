#include "deviceinfo.h"

#if defined (Q_OS_MAC)
#include <QBluetoothUuid>
#else
#include <QBluetoothAddress>
#endif

namespace il {

DeviceInfo::DeviceInfo(const QBluetoothDeviceInfo &info, QObject *parent)
    : QObject(parent)
    , m_device(info)
{
}

QString DeviceInfo::getName() const
{
    return m_device.name();
}

QString DeviceInfo::getAddress() const
{
    return getAddress(m_device);
}

void DeviceInfo::setDevice(const QBluetoothDeviceInfo &device)
{
    m_device = device;
    emit deviceChanged();
}

QString DeviceInfo::getAddress(const QBluetoothDeviceInfo &device)
{
#if defined(Q_OS_MAC)
    // workaround for Core Bluetooth:
    return device.deviceUuid().toString();
#else
    return device.address().toString();
#endif
}

}
