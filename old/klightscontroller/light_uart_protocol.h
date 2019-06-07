#ifndef LIGHT_UART_PROTOCOL_H
#define LIGHT_UART_PROTOCOL_H

#include <QDebug>
#include <QVector>
#include <QBluetoothUuid>

extern QBluetoothUuid LightUartProtocolUUID;


/*
 * Light Controller
 * Can be: 
 *  4 PWM channels
 *  2 analog channels
 * U? - get current state
 * response -> *3230300002 - analogic
 *             *FFFF000002 - max analogic channel state
 *             *2020202003 - PWM
 *             *191A1B1C03
 * US191A1B1C03 - set current state for 4 PWM Channels
 * US1F1F1F1F03
 * US1F1F000003 - set current state for 2 Analog Channels // padded with 30 * b bytes
 * UT0 - UT6 - save scene
 * UV0 - UV6 - read scene
 *  response -> *....
 * UI0 - UI6 - invoke scene
 *  response -> *....
 * UB0 - UB3 - Blink channel 0-3 | Blink times 1-9
 * 
 * All numbers values are encoded as hex strings, 1 value byte -> 2 hex chars
 */

class LightUartProtocol {
    const uint8_t noChannels = 4;
    const uint8_t maxAmplitude = 0x1F;
    const uint8_t startChar = 0x55;
    const uint8_t endChar = '\n'; // 0x0A
    const uint8_t paddingChar = 0x99;

    const uint8_t setCommandChar = 'S';
    const uint8_t getCommandChar = '?';

    QVector<uint8_t> currentState;

    QString currentStateBytes;

    LightUartProtocol() noexcept;

    QString setChannelValueAndGetCurrentStateBytes(uint8_t channel, uint8_t value);
    void setChannelCurrentState(uint8_t channel, uint8_t value);
    QString getCurrentStateBytes();
};

#endif // LIGHT_UART_PROTOCOL_H
