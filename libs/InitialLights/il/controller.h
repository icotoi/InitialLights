#pragma once

#include "icodable.h"
#include "light.h"

#include "QQmlAutoPropertyHelpers.h"
#include "QQmlObjectListModel.h"

#include <QLowEnergyController>
#include <QLowEnergyService>

namespace il {

class INITIALLIGHTSSHARED_EXPORT Controller : public QObject, public ICodable
{
public:
    enum ControllerType {
        UndefinedControllerType,
        V1_4xPWM,
        V1_1xPWM_1xRGB,
        V1_2x10V,
    };
    Q_ENUM(ControllerType)

private:
    Q_OBJECT

    QML_READONLY_AUTO_PROPERTY(il::Controller::ControllerType, controllerType)
    QML_READONLY_AUTO_PROPERTY(QString, name)
    QML_READONLY_AUTO_PROPERTY(QString, address)

    QML_READONLY_AUTO_PROPERTY(bool, isBusy)
    QML_READONLY_AUTO_PROPERTY(bool, isConnected)
    QML_READONLY_AUTO_PROPERTY(QString, message)

    QML_OBJMODEL_PROPERTY(il::Light, lights)

public:
    explicit Controller(QObject *parent = nullptr);
    explicit Controller(bool offline, QObject *parent = nullptr);
    explicit Controller(const QBluetoothDeviceInfo &info, QObject *parent = nullptr);
    ~Controller() override;

    void clear();
    void read(const QJsonObject& json) override;
    void write(QJsonObject& json) const override;

    // NOTE: when I try to use 'address' instead of 'safeAddress',
    //       the compiler fails to distinguish between this and the address() getter
    static QString safeAddress(const QBluetoothDeviceInfo &info);
    static bool isValidDevice(const QBluetoothDeviceInfo &info);

    void blink(Light *light, int offset);

public slots:
    void connectToController();
    void disconnectFromController();
    QByteArray updateDeviceCommand() const;

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
    bool writeToDevice(const QByteArray& data, bool clearReadBuffer = true);

    bool connectIfNeeded();

    Light* addNewLight(Light::LightType lightType, const QString& name);
    void connectLight(Light* light);

    QBluetoothDeviceInfo m_info;
    QScopedPointer<QLowEnergyController> m_controller;
    QScopedPointer<QLowEnergyService> m_service;
    QLowEnergyDescriptor m_notificationDescriptor;
    QByteArray m_command;
    bool m_hasReceivedInitialState { false };
    bool m_needsInitialState { true };
    QByteArray m_readBuffer;
    bool m_offline {false}; // for testing without network communication
};

} // namespace il
