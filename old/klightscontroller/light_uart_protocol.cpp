#include "light_uart_protocol.h"
#include <QVectorIterator>
#include <QDebug>
#include <QtBluetooth>

const QBluetoothUuid LightUartProtocol::UUID(QString("6E400001-B5A3-F393-E0A9-E50E24DCCA9E"));

LightUartProtocol::LightUartProtocol() noexcept
{
}

QString LightUartProtocol::setChannelValueAndGetCurrentStateBytes(uint8_t channel, uint8_t value)
{
    setChannelCurrentState(channel, value);
    return getCurrentStateBytes();
}

void LightUartProtocol::setChannelCurrentState(uint8_t channel, uint8_t value)
{
    if(channel > currentState.size()) {
        qDebug() << " [ERROR] Invalid channel: " << QString(channel) << endl;
        return;
    }

    if(value > maxAmplitude)
        value = maxAmplitude;

    currentState[channel] = value;

    qDebug() << " [INFO] Channel: " << QString::number(channel) << " <- " << QString::number(value);
}

QString LightUartProtocol::getCurrentStateBytes()
{
    QString bytes;

    bytes.append(startChar);
    bytes.append(setCommandChar);

    for(auto& x : currentState) {
        bytes.append(QString::number(x, 16));
    }

    bytes.append(QString::number(paddingChar, 16));
    bytes.append(endChar);

    bytes = bytes.toUpper();

    qDebug() << " [INFO] command: " << bytes << endl;

    return bytes;
}
