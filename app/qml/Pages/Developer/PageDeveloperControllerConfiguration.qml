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
            kind: controller ? controller.kind : Controller.Unknown
            isOnline: controller ? controller.isOnline : false
            isEnabled: controller ? controller.isEnabled : false
        }

        ILTextField {
            textField.text: controller ? controller.name : ""
            Layout.fillWidth: true
            placeholderText: qsTr("Controller name")
            textField.onEditingFinished: if (controller) controller.name = textField.text
        }

        GroupBox {
            id: groupBox
            title: "Kind:"
            Layout.fillWidth: true

            ColumnLayout {
                anchors.right: parent.right
                anchors.left: parent.left
                RadioButton {
                    text: "Unknown"
                    checked: controller ? controller.kind === Controller.Unknown : false
                    onCheckedChanged: if (checked) controller.kind = Controller.Unknown
                    Layout.fillWidth: true
                }

                RadioButton {
                    text: "RGBW"
                    checked: controller ? controller.kind === Controller.RGBW : false
                    Layout.fillWidth: true
                    onCheckedChanged: if (checked) controller.kind = Controller.RGBW
                }

                RadioButton {
                    text: "Analogic"
                    checked: controller ? controller.kind === Controller.Analogic : false
                    Layout.fillWidth: true
                    onCheckedChanged: if (checked) controller.kind = Controller.Analogic
                }
            }
        }

        GroupBox {
            id: groupBox1
            Layout.fillWidth: true
            title: "Lights"

            ColumnLayout {
                anchors.right: parent.right
                anchors.left: parent.left

                Repeater {
                    id: repeater
                    model: controller ? controller.lights.items : null

                    delegate: ColumnLayout {
                        property var light: controller ? controller.lights.items.get(index) : null

                        Layout.fillWidth: true

                        Text {
                            text: model.name
                            font.bold: true
                        }

                        GridLayout {
                            Layout.fillWidth: true
                            columns: 2
                            visible: model.kind === LightKind.RGBW

                            Text { text: "red" }

                            Slider {
                                Layout.fillWidth: true
                                from: 0
                                to: 255
                                stepSize: 1
                                snapMode: Slider.SnapAlways
                                onValueChanged: light.red = value
                            }

                            Text { text: "green" }

                            Slider {
                                Layout.fillWidth: true
                                from: 0
                                to: 255
                                stepSize: 1
                                snapMode: Slider.SnapAlways
                                onValueChanged: light.green = value
                            }

                            Text { text: "blue" }

                            Slider {
                                Layout.fillWidth: true
                                from: 0
                                to: 255
                                stepSize: 1
                                snapMode: Slider.SnapAlways
                                onValueChanged: light.blue = value
                            }

                            Text { text: "white" }

                            Slider {
                                Layout.fillWidth: true
                                from: 0
                                to: 255
                                stepSize: 1
                                snapMode: Slider.SnapAlways
                                onValueChanged: light.white = value
                            }
                        }

                        Slider {
                            Layout.fillWidth: true
                            visible: model.kind === LightKind.Analogic
                            from: 0
                            to: 255
                            stepSize: 1
                            snapMode: Slider.SnapAlways
                            onValueChanged: if (light) light.value = value
                            value: light && light.value ? light.value : 0
                        }
                    }
                }
            }
        }

        RowLayout {
            Text {
                text: "Enabled"
            }

            Switch {
                checked: controller ? controller.isEnabled : false
                onCheckedChanged: if (controller) controller.isEnabled = checked
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
