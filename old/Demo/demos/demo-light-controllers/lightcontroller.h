#pragma once

#include "abstractlightcontroller.h"

#include <QLowEnergyController>
#include <QLowEnergyService>

namespace il {

class LightController : public AbstractLightController
{
    Q_OBJECT

public:
    explicit LightController(const QBluetoothDeviceInfo &info, QObject *parent = nullptr);
    ~LightController() override;

    static QString address(const QBluetoothDeviceInfo &info);
    static bool isValidDevice(const QBluetoothDeviceInfo &info);

    void clear() override;

public slots:
    void connectToController() override;
    void disconnectFromController() override;

private:
    //QLowEnergyController
    void serviceDiscovered(const QBluetoothUuid &);
    void serviceScanDone();
    void controllerError(QLowEnergyController::Error);
    void controllerConnected();
    void controllerDisconnected();

    //QLowEnergyService
    void serviceStateChanged(QLowEnergyService::ServiceState state);
    void serviceCharacteristicChanged(const QLowEnergyCharacteristic &characteristic,
                              const QByteArray &data);
    void serviceDescriptorWritten(const QLowEnergyDescriptor &descriptor,
                                  const QByteArray &data);
    void serviceError(QLowEnergyService::ServiceError e);

    void updateFromDevice(const QByteArray& data);
    void updateDevice();
    bool writeToDevice(const QByteArray& data);

    QBluetoothDeviceInfo m_info;
    QScopedPointer<QLowEnergyController> m_controller;
    QScopedPointer<QLowEnergyService> m_service;
    QLowEnergyDescriptor m_notificationDescriptor;
    QByteArray m_command;
    bool m_hasReceivedInitialState { false };
};

} // namespace il
