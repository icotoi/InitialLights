/***************************************************************************
**
** Copyright (C) 2014 BlackBerry Limited. All rights reserved.
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

import QtQuick 2.0
import QtQuick.Particles 2.0
import QtQuick.Controls 2.5


Rectangle {
    id: screenMonitor
    color: "#F0EBED"

    Button {
        id:menu
        width: parent.width
        height: 0.1 * parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        text: "Back"
        onClicked: {
            lightsUart.disconnectService();
            pageLoader.source="home.qml";
        }
    }

    Rectangle {
        id: rectangle1
        x: 0
        height: 75
        anchors.top: menu.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        Text {
            id: channel1Value
            font.pointSize: 24; font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter

            color: "#3870BA"
            text: lightsUart.channel1
            anchors.top: parent.top
            anchors.topMargin: 0
        }

        Slider {
            id: channel1Slider
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.horizontalCenter: parent.horizontalCenter
            value: lightsUart.channel1SliderValue
            onValueChanged: {
                lightsUart.channel1SliderValue = value
            }
        }
    }

    Rectangle {
        id: rectangle2
        x: 0
        height: 75
        anchors.top: rectangle1.bottom
        anchors.topMargin: 0
        anchors.horizontalCenter: parent.horizontalCenter
        Text {
            id: channel2Value
            font.pointSize: 24; font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter

            color: "#3870BA"
            text: lightsUart.channel2
            anchors.top: parent.top
            anchors.topMargin: 0
        }

        Slider {
            id: channel2Slider
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.horizontalCenter: parent.horizontalCenter
            value: lightsUart.channel2SliderValue
            onValueChanged: {
                lightsUart.channel2SliderValue = value
            }
        }
    }

    Rectangle {
        id: rectangle3
        x: 0
        height: 75
        anchors.top: rectangle2.bottom
        anchors.topMargin: 0
        anchors.horizontalCenter: parent.horizontalCenter
        Text {
            id: channel3Value
            font.pointSize: 24; font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter

            color: "#3870BA"
            text: lightsUart.channel3
            anchors.top: parent.top
            anchors.topMargin: 0
        }

        Slider {
            id: channel3Slider
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.horizontalCenter: parent.horizontalCenter
            value: lightsUart.channel3SliderValue
            onValueChanged: {
                lightsUart.channel3SliderValue = value
            }
        }
    }

    Rectangle {
        id: rectangle4
        x: 0
        height: 75
        anchors.top: rectangle3.bottom
        anchors.topMargin: 0
        anchors.horizontalCenter: parent.horizontalCenter
        Text {
            id: channel4Value
            font.pointSize: 24; font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter

            color: "#3870BA"
            text: lightsUart.channel4
            anchors.top: parent.top
            anchors.topMargin: 0
        }

        Slider {
            id: channel4Slider
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.horizontalCenter: parent.horizontalCenter
            value: lightsUart.channel4SliderValue
            onValueChanged: {
                lightsUart.channel4SliderValue = value
            }
        }
    }



    Rectangle {
        id: updatei
        width: parent.width
        height: 80
        anchors.bottom: stop.top

        color: "#F0EBED"
        border.color: "#3870BA"
        border.width: 2

        Text {
            id: logi
            text: lightsUart.message
            anchors.centerIn: updatei
            color: "#3870BA"
        }
    }


    Button {
        id:stop
        width: parent.width
        height: 0.1*parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        text: "Disconnect"
        onClicked: {
            lightsUart.disconnectService();
            pageLoader.source = "main.qml";
        }
    }

}


/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
