import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "Images"
import "Controls"

Item {
    id: element
    width: 360
    height: 590
    property alias temperatureSlider: temperatureSlider
    property alias intensitySlider: intensitySlider
    property alias onSwitch: onSwitch
    property alias configurationPane: configurationPane
    property alias iLCircularToggleLedButton2: iLCircularToggleLedButton2
    property alias iLCircularToggleLedButton1: iLCircularToggleLedButton1
    property alias iLCircularToggleLedButton0: iLCircularToggleLedButton0
    property alias imageMouseArea: imageMouseArea
    clip: true


    Item {
        id: controlContainer
        x: 15
        y: 0
        width: 330
        height: 330
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

        Image {
            id: image
            anchors.fill: parent
            fillMode: Image.PreserveAspectFit
            source: "Images/pixabay_illumination-lights-bulbs-731494_1920.jpg"
        }

        MouseArea {
            id: imageMouseArea
            anchors.fill: parent
        }


        ILCircularToggleLedButton {
            id: iLCircularToggleLedButton0
            x: 33
            y: 187
            color: "#00ffff"
            lightTemperature: 0.9
            lightIntensity: 0.2
        }

        ILCircularToggleLedButton {
            id: iLCircularToggleLedButton1
            x: 97
            y: 111
            color: "#ffff00"
        }

        ILCircularToggleLedButton {
            id: iLCircularToggleLedButton2
            x: 119
            y: 201
            color: "#ffffff"
            isOn: true
            lightIntensity: 0.5
            lightTemperature: 1
        }

    }

    Pane {
        id: configurationPane
        visible: false
        anchors.rightMargin: 16
        anchors.leftMargin: 16
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        ColumnLayout {
            id: columnLayout
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right

            RowLayout {
                id: rowLayout
                Layout.fillWidth: true

                Label {
                    id: label
                    text: qsTr("Power")
                    Layout.fillWidth: true
                }

                Switch {
                    id: onSwitch
                    display: AbstractButton.IconOnly
                }

            }

            Label {
                id: label1
                text: qsTr("Intensity")
            }

            Slider {
                id: intensitySlider
                Layout.fillWidth: true
                value: 0.5
            }

            Label {
                id: label2
                text: qsTr("Temperature")
            }

            Slider {
                id: temperatureSlider
                Layout.fillWidth: true
                value: 0.5
            }
        }
    }
}




































/*##^## Designer {
    D{i:2;anchors_x:108;anchors_y:138}D{i:3;anchors_height:100;anchors_width:100}D{i:4;anchors_x:108;anchors_y:138}
D{i:1;anchors_width:100}
}
 ##^##*/
