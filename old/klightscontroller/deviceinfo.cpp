#include "deviceinfo.h"
#include <QBluetoothUuid>

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
#ifdef Q_OS_MAC
    // workaround for Core Bluetooth:
    return m_device.deviceUuid().toString();
#else
    return m_device.address().toString();
#endif
}

void DeviceInfo::setDevice(const QBluetoothDeviceInfo &device)
{
    m_device = device;
    emit deviceChanged();
}

}
