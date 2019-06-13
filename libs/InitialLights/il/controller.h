#pragma once

#include "controllerbase.h"

#include <QLowEnergyController>
#include <QLowEnergyService>

namespace il {

class INITIALLIGHTSSHARED_EXPORT Controller : public ControllerBase
{
    Q_OBJECT

public:
    explicit Controller(QObject *parent = nullptr);
    explicit Controller(const QBluetoothDeviceInfo &info, QObject *parent = nullptr);
    ~Controller() override;

    // NOTE: when I try to use 'address' instead of 'safeAddress',
    //       the compiler fails to distinguish between this and the address() getter
    static QString safeAddress(const QBluetoothDeviceInfo &info);
    static bool isValidDevice(const QBluetoothDeviceInfo &info);

    void clear() override;
    void read(const QJsonObject& json) override;

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
