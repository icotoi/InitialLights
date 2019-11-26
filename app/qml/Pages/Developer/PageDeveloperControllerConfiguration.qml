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
                    model: controller ? controller.lights.items : null
                    delegate: RowLayout {
                        Rectangle {
                            width: 30
                            height: width
                            radius: width / 2
                            color: "#f9e79f"
                            border.color: "#979a9a"
                        }

                        ColumnLayout {
                            Text {
                                text: model.name
                            }
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
