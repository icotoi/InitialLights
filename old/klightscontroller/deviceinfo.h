#pragma once

#include <QObject>
#include <QBluetoothDeviceInfo>

class DeviceInfo: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString deviceName READ getName NOTIFY deviceChanged)
    Q_PROPERTY(QString deviceAddress READ getAddress NOTIFY deviceChanged)

public:
    explicit DeviceInfo(const QBluetoothDeviceInfo &device, QObject* parent = nullptr);

    QString getName() const;
    QString getAddress() const;

    QBluetoothDeviceInfo getDevice() const { return m_device; }
    void setDevice(const QBluetoothDeviceInfo &device);

signals:
    void deviceChanged();

private:
    QBluetoothDeviceInfo m_device;
};

