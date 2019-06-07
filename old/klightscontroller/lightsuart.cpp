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

#include "lightsuart.h"

#include <QtEndian>

LightsUart::LightsUart():
    m_currentDevice(QBluetoothDeviceInfo()), foundUartService(false),
    m_max(0), m_min(0), calories(0), m_control(0), timer(0),
    m_service(0)
{
    m_deviceDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);

    connect(m_deviceDiscoveryAgent, SIGNAL(deviceDiscovered(const QBluetoothDeviceInfo&)),
            this, SLOT(addDevice(const QBluetoothDeviceInfo&)));
    connect(m_deviceDiscoveryAgent, SIGNAL(error(QBluetoothDeviceDiscoveryAgent::Error)),
            this, SLOT(deviceScanError(QBluetoothDeviceDiscoveryAgent::Error)));
    connect(m_deviceDiscoveryAgent, SIGNAL(finished()), this, SLOT(scanFinished()));

    // initialize random seed for demo mode
    qsrand(QTime::currentTime().msec());
}

LightsUart::~LightsUart()
{
    qDeleteAll(m_devices);
    m_devices.clear();
}

void LightsUart::deviceSearch()
{
    qDeleteAll(m_devices);
    m_devices.clear();
    m_deviceDiscoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
    setMessage("Scanning for devices...");
}

void LightsUart::addDevice(const QBluetoothDeviceInfo &device)
{
    if (device.serviceUuids().contains(uartServiceUuid))
    {
        qWarning() << "Discovered LE Device name: " << device.name() << " Address: "
                   << device.address().toString();
        DeviceInfo *dev = new DeviceInfo(device);
        m_devices.append(dev);
        setMessage("Low Energy device found. Scanning for more...");
    }
    //...
}

void LightsUart::scanFinished()
{
    if (m_devices.size() == 0)
        setMessage("No Low Energy devices found");
    Q_EMIT nameChanged();
}

void LightsUart::deviceScanError(QBluetoothDeviceDiscoveryAgent::Error error)
{
    if (error == QBluetoothDeviceDiscoveryAgent::PoweredOffError)
        setMessage("The Bluetooth adaptor is powered off, power it on before doing discovery.");
    else if (error == QBluetoothDeviceDiscoveryAgent::InputOutputError)
        setMessage("Writing or reading from the device resulted in an error.");
    else
        setMessage("An unknown error has occurred.");
}

void LightsUart::setMessage(QString message)
{
    m_info = message;
    Q_EMIT messageChanged();
}

QString LightsUart::message() const
{
    return m_info;
}

QVariant LightsUart::name()
{
    return QVariant::fromValue(m_devices);
}

float LightsUart::getChannel4SliderValue() const
{
    return channel4SliderValue;
}

void LightsUart::setChannel4SliderValue(float value)
{
    channel4SliderValue = value;
    updateUartValueState();
}

float LightsUart::getChannel3SliderValue() const
{
    return channel3SliderValue;
}

void LightsUart::setChannel3SliderValue(float value)
{
    channel3SliderValue = value;
    updateUartValueState();
}

float LightsUart::getChannel2SliderValue() const
{
    return channel2SliderValue;
}

void LightsUart::setChannel2SliderValue(float value)
{
    channel2SliderValue = value;
    updateUartValueState();
}

float LightsUart::getChannel1SliderValue() const
{
    return channel1SliderValue;
}

void LightsUart::setChannel1SliderValue(float value)
{
    channel1SliderValue = value;
    updateUartValueState();
}

int LightsUart::getChannel4() const
{
    return channel4;
}

int LightsUart::getChannel3() const
{
    return channel3;
}

int LightsUart::getChannel2() const
{
    return channel2;
}

int LightsUart::getChannel1() const
{
    return channel1;
}

void LightsUart::connectToService(const QString &address)
{
    m_measurements.clear();

    m_haveReceivedUartInitialState = false;

    bool deviceFound = false;
    for (int i = 0; i < m_devices.size(); i++) {
        if (((DeviceInfo*)m_devices.at(i))->getAddress() == address ) {
            m_currentDevice.setDevice(((DeviceInfo*)m_devices.at(i))->getDevice());
            setMessage("Connecting to device...");
            deviceFound = true;
            break;
        }
    }
    // we are running demo mode
    if (!deviceFound) {
        startDemo();
        return;
    }

    if (m_control) {
        m_control->disconnectFromDevice();
        delete m_control;
        m_control = 0;

    }
    m_control = new QLowEnergyController(m_currentDevice.getDevice(), this);
    connect(m_control, SIGNAL(serviceDiscovered(QBluetoothUuid)),
            this, SLOT(serviceDiscovered(QBluetoothUuid)));
    connect(m_control, SIGNAL(discoveryFinished()),
            this, SLOT(serviceScanDone()));
    connect(m_control, SIGNAL(error(QLowEnergyController::Error)),
            this, SLOT(controllerError(QLowEnergyController::Error)));
    connect(m_control, SIGNAL(connected()),
            this, SLOT(deviceConnected()));
    connect(m_control, SIGNAL(disconnected()),
            this, SLOT(deviceDisconnected()));

    m_control->connectToDevice();
}


void LightsUart::deviceConnected()
{
    m_control->discoverServices();
}

void LightsUart::deviceDisconnected()
{
    setMessage("Heart Rate service disconnected");
    qWarning() << "Remote device disconnected";
}


void LightsUart::serviceDiscovered(const QBluetoothUuid &gatt)
{
    if (gatt == uartServiceUuid) {
        setMessage("UART service discovered. Waiting for service scan to be done...");
        qDebug() << "UART service discovered. Waiting for service scan to be done...";
        foundUartService = true;
    }
}

void LightsUart::serviceScanDone()
{
    delete m_service;
    m_service = 0;

    if (foundUartService) {
        setMessage("Connecting to service...");
        m_service = m_control->createServiceObject(uartServiceUuid, this);
    }

    if (!m_service) {
        setMessage("UART Service not found.");
        return;
    }

    connect(m_service, SIGNAL(stateChanged(QLowEnergyService::ServiceState)),
            this, SLOT(serviceStateChanged(QLowEnergyService::ServiceState)));
    connect(m_service, SIGNAL(characteristicChanged(QLowEnergyCharacteristic,QByteArray)),
            this, SLOT(receivedUartResponse(QLowEnergyCharacteristic,QByteArray)));
    connect(m_service, SIGNAL(descriptorWritten(QLowEnergyDescriptor,QByteArray)),
            this, SLOT(confirmedDescriptorWrite(QLowEnergyDescriptor,QByteArray)));

    m_service->discoverDetails();
}

void LightsUart::disconnectService()
{
    foundUartService = false;
    m_stop = QDateTime::currentDateTime();

    if (m_devices.isEmpty()) {
        if (timer)
            timer->stop();
        return;
    }

    //disable notifications before disconnecting
    if (m_notificationDesc.isValid() && m_service
            && m_notificationDesc.value() == QByteArray::fromHex("0100"))
    {
        m_service->writeDescriptor(m_notificationDesc, QByteArray::fromHex("0000"));
    } else {
        m_control->disconnectFromDevice();
        delete m_service;
        m_service = 0;
    }
}

void LightsUart::controllerError(QLowEnergyController::Error error)
{
    setMessage("Cannot connect to remote device.");
    qWarning() << "Controller Error:" << error;
}

void LightsUart::serviceStateChanged(QLowEnergyService::ServiceState s)
{
    qDebug() << "aici";
    switch (s) {
    case QLowEnergyService::ServiceDiscovered:
    {
        qDebug() << "aici 3";

        const QLowEnergyCharacteristic uartChar = m_service->characteristic(uartReadCharUuid);
        if (!uartChar.isValid()) {
            setMessage("UART Data not found.");
            qDebug() << "UART Data not found.";
            break;
        }

        qDebug() << "serviceStateChanged";

        m_notificationDesc = uartChar.descriptor(QBluetoothUuid::ClientCharacteristicConfiguration);
        if (m_notificationDesc.isValid()) {
            qDebug() << "aici 2222";

            m_service->writeDescriptor(m_notificationDesc, QByteArray::fromHex("0100"));
            setMessage("Connected");
            m_start = QDateTime::currentDateTime();

            const QLowEnergyCharacteristic uartWriteChar = m_service->characteristic(uartWriteCharUuid);
            m_lastUartCmd = QString("U?\n");
            m_service->writeCharacteristic(uartWriteChar, m_lastUartCmd.toUtf8(),  QLowEnergyService::WriteMode::WriteWithoutResponse);
        }

        break;
    }
    default:
        //nothing for now
        break;
    }
}

void LightsUart::serviceError(QLowEnergyService::ServiceError e)
{
    switch (e) {
    case QLowEnergyService::DescriptorWriteError:
        setMessage("Cannot obtain HR notifications");
        break;
    default:
        qWarning() << "HR service error:" << e;
    }
}

void LightsUart::receivedUartResponse(const QLowEnergyCharacteristic &c,
                                      const QByteArray &value)
{
    // ignore any other characteristic change -> shouldn't really happen though
    if (c.uuid() != QBluetoothUuid(uartReadCharUuid))
        return;

    QString uartResponse = QString(value);

    qDebug() << "receivedUartResponse: " << uartResponse;

    updateFromUartValues(uartResponse);
}

void LightsUart::confirmedDescriptorWrite(const QLowEnergyDescriptor &d,
                                          const QByteArray &value)
{
    if (d.isValid() && d == m_notificationDesc && value == QByteArray::fromHex("0000")) {
        //disabled notifications -> assume disconnect intent
        m_control->disconnectFromDevice();
        delete m_service;
        m_service = 0;
    }
}

void LightsUart::obtainResults()
{
}

int LightsUart::measurements(int index) const
{
    if (index > m_measurements.size())
        return 0;
    else
        return (int)m_measurements.value(index);
}

int LightsUart::measurementsSize() const
{
    return m_measurements.size();
}

QString LightsUart::deviceAddress() const
{
    return m_currentDevice.getAddress();
}

int LightsUart::numDevices() const
{
    return m_devices.size();
}

void LightsUart::startDemo()
{
    m_start = QDateTime::currentDateTime();
    if (!timer) {
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(receiveDemo()));
    }
    timer->start(1000);
    setMessage("This is Demo mode");
}

void LightsUart::receiveDemo()
{
    m_measurements.append(randomPulse());
    Q_EMIT lightChannelsValueChanged();
}

int LightsUart::randomPulse() const
{
    // random number between 50 and 70
    return qrand() % (70 - 50) + 50;
}

void LightsUart::updateUartValueState()
{
    channel1 = channel1SliderValue * (float)0x1F;
    channel2 = channel2SliderValue * (float)0x1F;
    channel3 = channel3SliderValue * (float)0x1F;
    channel4 = channel4SliderValue * (float)0x1F;

    QString toSend = QString("US");

    toSend.append(QString::number(channel1, 16).rightJustified(2, '0'));
    toSend.append(QString::number(channel2, 16).rightJustified(2, '0'));
    toSend.append(QString::number(channel3, 16).rightJustified(2, '0'));
    toSend.append(QString::number(channel4, 16).rightJustified(2, '0'));
    toSend.append("03");
    toSend.append("\n");

    if(toSend.length() != 13) {
        qDebug() << "ERROR: BLE SET CMD TO LONG!!!";
        return;
    }

    if (m_lastUartCmd.compare(toSend) != 0) {
        qDebug() << "toSend:" << toSend;

        m_lastUartCmd = toSend;

        Q_EMIT lightChannelsValueChanged();

        if(m_lastUartCmd.contains("U?")) {
            m_lastUartCmd = "";
        } else {
            if(m_haveReceivedUartInitialState) {
                qDebug() << "BLE SENDING:" << toSend;
                const QLowEnergyCharacteristic uartWriteChar = m_service->characteristic(uartWriteCharUuid);
                m_service->writeCharacteristic(uartWriteChar, toSend.toUtf8(),  QLowEnergyService::WriteMode::WriteWithoutResponse);
            }
        }
    }

}

void LightsUart::updateFromUartValues(QString uartStr)
{
    if(uartStr.startsWith("*")) {
        QString data = uartStr.mid(1);

        if(m_lastUartCmd.startsWith("U?")) {

            if(!m_haveReceivedUartInitialState)
                m_haveReceivedUartInitialState = true;

            // Current controller values
            QString channel1Str = data.mid(0, 2);
            channel1 = channel1Str.toInt(nullptr, 16);
            channel1SliderValue = float(channel1)/31.00F;

            QString channel2Str = data.mid(2, 2);
            channel2 = channel2Str.toInt(nullptr, 16);
            if(channel2 == 0)
                channel2SliderValue = 0;
            else
                channel2SliderValue = float(channel2)/31.00F;

            QString channel3Str = data.mid(4, 2);
            channel3 = channel3Str.toInt(nullptr, 16);
            if(channel3 == 0)
                channel3SliderValue = 0;
            else
                channel3SliderValue = float(channel3)/31.00F;

            QString channel4Str = data.mid(6, 2);
            channel4 = channel4Str.toInt(nullptr, 16);
            if(channel4 == 0)
                channel4SliderValue = 0;
            else
                channel4SliderValue = float(channel4)/31.00F;

            qDebug() << "Channels:" << QString::number(channel1) << QString::number(channel2) << QString::number(channel3) << QString::number(channel4);
            qDebug() << "Sliders:" << channel1SliderValue << channel2SliderValue << channel3SliderValue << channel4SliderValue;

            Q_EMIT lightChannelsValueChanged();

        } else if(m_lastUartCmd.startsWith("UV")) {
        } else if(m_lastUartCmd.startsWith("UI")) {
        }
    }
}

