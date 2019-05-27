import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "Images"
import "Controls"
import "Constants"

Item {
    id: element
    property alias colorRectangleMouseArea: colorRectangleMouseArea
    property alias colorRectangle: colorRectangle
    property alias deleteLightButton: deleteLightButton
    property alias addLightButton: addLightButton
    property alias roomView: roomView
    property alias temperatureSlider: temperatureSlider
    property alias intensitySlider: intensitySlider
    property alias onSwitch: onSwitch
    property alias configurationPane: configurationPane
    clip: true

    ILRoomView {
        id: roomView

        y: 0
        width: 330
        height: 330
        anchors.horizontalCenter: parent.horizontalCenter
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

        image: "Images/pixabay_illumination-lights-bulbs-731494_1920.jpg"

        ILRoomLight {
            x: 35
            y: 184
            color: "#00ffff"
            lightTemperature: 0.9
            lightIntensity: 0.2
        }

        ILRoomLight {
            x: 96
            y: 110
            color: "#ffff00"
        }

        ILRoomLight {
            x: 120
            y: 198
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
                    Layout.fillWidth: false
                }

                Switch {
                    id: onSwitch
                    display: AbstractButton.IconOnly
                }

                Item {
                    visible: true
                    Layout.fillWidth: true
                }

                Rectangle {
                    id: colorRectangle
                    color: "white"

                    width: ILStyle.colorRectangle.size
                    height: width
                    radius: ILStyle.colorRectangle.radius
                    border.width: ILStyle.colorRectangle.borderWidth
                    border.color: ILStyle.colorRectangle.borderColor

                    MouseArea {
                        id: colorRectangleMouseArea
                        anchors.fill: parent
                    }
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

    ToolButton {
        id: addLightButton
        y: 0
        icon.source: "Images/material.io-sharp-add-24px.svg"
    }

    ToolButton {
        id: deleteLightButton
        visible: configurationPane.visible
        icon.source: "Images/material.io-sharp-delete-24px.svg"
    }
}






/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:12;anchors_height:100;anchors_width:100}
D{i:16;anchors_y:0}D{i:17;anchors_y:0}
}
 ##^##*/
