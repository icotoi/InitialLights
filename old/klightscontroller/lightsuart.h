/***************************************************************************
**
** Copyright (C) 2014 BlackBerry Limited. All rights reserved.
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the QtBluetooth module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef HEARTRATE_H
#define HEARTRATE_H

#include "deviceinfo.h"

#include <QString>
#include <QDebug>
#include <QDateTime>
#include <QVector>
#include <QTimer>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothDeviceInfo>
#include <QLowEnergyController>
#include <QLowEnergyService>

QT_USE_NAMESPACE
class LightsUart: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariant name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString message READ message NOTIFY messageChanged)

    Q_PROPERTY(int channel1 READ getChannel1 NOTIFY lightChannelsValueChanged)
    Q_PROPERTY(int channel2 READ getChannel2 NOTIFY lightChannelsValueChanged)
    Q_PROPERTY(int channel3 READ getChannel3 NOTIFY lightChannelsValueChanged)
    Q_PROPERTY(int channel4 READ getChannel4 NOTIFY lightChannelsValueChanged)

    Q_PROPERTY(float channel1SliderValue READ getChannel1SliderValue WRITE setChannel1SliderValue NOTIFY lightChannelsValueChanged)
    Q_PROPERTY(float channel2SliderValue READ getChannel2SliderValue WRITE setChannel2SliderValue NOTIFY lightChannelsValueChanged)
    Q_PROPERTY(float channel3SliderValue READ getChannel3SliderValue WRITE setChannel3SliderValue NOTIFY lightChannelsValueChanged)
    Q_PROPERTY(float channel4SliderValue READ getChannel4SliderValue WRITE setChannel4SliderValue NOTIFY lightChannelsValueChanged)

public:
    LightsUart();
    ~LightsUart();
    void setMessage(QString message);
    QString message() const;
    QVariant name();

    int channel1;
    int channel2;
    int channel3;
    int channel4;

    float channel1SliderValue;
    float channel2SliderValue;
    float channel3SliderValue;
    float channel4SliderValue;

    QBluetoothUuid uartServiceUuid = QBluetoothUuid(QStringLiteral("6E400001-B5A3-F393-E0A9-E50E24DCCA9E"));
    QBluetoothUuid uartWriteCharUuid = QBluetoothUuid(QStringLiteral("6E400002-B5A3-F393-E0A9-E50E24DCCA9E"));
    QBluetoothUuid uartReadCharUuid = QBluetoothUuid(QStringLiteral("6E400003-B5A3-F393-E0A9-E50E24DCCA9E"));

    int getChannel1() const;
    int getChannel2() const;
    int getChannel3() const;
    int getChannel4() const;

    float getChannel1SliderValue() const;
    void setChannel1SliderValue(float value);

    float getChannel2SliderValue() const;
    void setChannel2SliderValue(float value);

    float getChannel3SliderValue() const;
    void setChannel3SliderValue(float value);

    float getChannel4SliderValue() const;
    void setChannel4SliderValue(float value);

public slots:
    void deviceSearch();
    void connectToService(const QString &address);
    void disconnectService();
    void startDemo();

    void obtainResults();
    int measurements(int index) const;
    int measurementsSize() const;
    QString deviceAddress() const;
    int numDevices() const;

private slots:
    //QBluetothDeviceDiscoveryAgent
    void addDevice(const QBluetoothDeviceInfo&);
    void scanFinished();
    void deviceScanError(QBluetoothDeviceDiscoveryAgent::Error);

    //QLowEnergyController
    void serviceDiscovered(const QBluetoothUuid &);
    void serviceScanDone();
    void controllerError(QLowEnergyController::Error);
    void deviceConnected();
    void deviceDisconnected();

    //QLowEnergyService
    void serviceStateChanged(QLowEnergyService::ServiceState s);
    void receivedUartResponse(const QLowEnergyCharacteristic &c,
                              const QByteArray &value);
    void confirmedDescriptorWrite(const QLowEnergyDescriptor &d,
                              const QByteArray &value);
    void serviceError(QLowEnergyService::ServiceError e);

    //DemoMode
    void receiveDemo();

Q_SIGNALS:
    void messageChanged();
    void nameChanged();
    void lightChannelsValueChanged();

private:
    int randomPulse() const;

    DeviceInfo m_currentDevice;
    QBluetoothDeviceDiscoveryAgent *m_deviceDiscoveryAgent;
    QLowEnergyDescriptor m_notificationDesc;
    QList<QObject*> m_devices;
    QString m_info;
    bool foundUartService;
    QVector<quint16> m_measurements;
    QDateTime m_start;
    QDateTime m_stop;
    int m_max;
    int m_min;
    float calories;
    QLowEnergyController *m_control;
    QTimer *timer; // for demo application
    QLowEnergyService *m_service;

    QString m_lastUartCmd;
    bool m_haveReceivedUartInitialState;

    void updateUartValueState();
    void updateFromUartValues(QString uartStr);
};

#endif // HEARTRATE_H

