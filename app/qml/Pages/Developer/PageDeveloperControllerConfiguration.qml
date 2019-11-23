import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import "../../Constants"
import "../../Controls"
import InitialLights 1.0

Page {
    id: root

    property var controller

    signal canceled()

    implicitWidth: 360
    implicitHeight: 640

    ColumnLayout {
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.left: parent.left
        enabled: controller ? controller.isOnline : false

        ILControllerSetupDelegate {
            Layout.fillWidth: true
            name: controller ? controller.name : ""
            address: controller ? controller.address : ""
            controllerState: controller ? controller.state : Controller.NotConfigured
            isOnline: controller ? controller.isOnline : false
        }

        ILTextField {
            textField.text: controller ? controller.name : ""
            Layout.fillWidth: true
            placeholderText: qsTr("Controller name")
            textField.onEditingFinished: if (controller) controller.name = textField.text
        }

        Text {
            text: "LEDs (0-255):"
        }

        GridLayout {
            id: gridLayout
            width: 100
            height: 100
            columns: 2

            Text {
                text: channel1Slider.value
                horizontalAlignment: Text.AlignRight
                Layout.minimumWidth: 40
            }

            Slider {
                id: channel1Slider
                snapMode: Slider.SnapAlways
                stepSize: 1
                to: 255
                Layout.fillWidth: true
            }

            Text {
                text: channel2Slider.value
                Layout.minimumWidth: 40
                horizontalAlignment: Text.AlignRight
            }

            Slider {
                id: channel2Slider
                snapMode: Slider.SnapAlways
                stepSize: 1
                to: 255
                Layout.fillWidth: true
            }

            Text {
                text: channel3Slider.value
                horizontalAlignment: Text.AlignRight
                Layout.minimumWidth: 40
            }

            Slider {
                id: channel3Slider
                snapMode: Slider.SnapAlways
                stepSize: 1
                to: 255
                Layout.fillWidth: true
            }

            Text {
                text: channel4Slider.value
                horizontalAlignment: Text.AlignRight
                Layout.minimumWidth: 40
            }

            Slider {
                id: channel4Slider
                snapMode: Slider.SnapAlways
                stepSize: 1
                to: 255
                Layout.fillWidth: true
            }
        }
    }

    ILToolButton {
        width: 32
        height: 32
        anchors.top: parent.top
        anchors.right: parent.right
        padding: 8
        icon.source: "../../Images/Icon-16-Cancel.svg"
        onClicked: {
            console.log("canceled")
            root.canceled()
        }
    }
}
