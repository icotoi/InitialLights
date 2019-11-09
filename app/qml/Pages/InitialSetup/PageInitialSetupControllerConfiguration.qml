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

    Rectangle {
        anchors.fill: parent
        color: "#ffffff"
    }

    Flickable {
        anchors.fill: parent
        contentHeight: columnLayout.height
        ScrollIndicator.vertical: ScrollIndicator {}

        ColumnLayout {
            id: columnLayout
            spacing: 32
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.left: parent.left

            Rectangle {
                color: "#F3F4F5"
                Layout.fillWidth: true

                implicitHeight: headerColumnLayout.height

                ColumnLayout {
                    id: headerColumnLayout
                    anchors.right: parent.right
                    anchors.left: parent.left

                    ILTitleText {
                        text : qsTr("Enable controller")
                        Layout.topMargin: 50
                        horizontalAlignment: Text.AlignHCenter
                        Layout.fillWidth: true
                        size: ILStyle.TextSize.Medium
                    }

                    ILInfoText {
                        text: qsTr("Quickly add lights for this controller")
                        Layout.bottomMargin: 20
                        horizontalAlignment: Text.AlignHCenter
                        Layout.fillWidth: true
                        size: ILStyle.TextSize.Medium
                    }

                }
            }

            ILConfigurationStep {
                Layout.rightMargin: 20
                Layout.leftMargin: 20
                Layout.fillWidth: true
                stepLine.anchors.bottomMargin: -32
                stepId: "1"
                title: qsTr("Change the controller name")
                info: qsTr("Adding a specific name to the controller would
help to distinct them in the future")

                contents: ILTextField {
                    textField.text: controller ? controller.name : ""
                    Layout.fillWidth: true
                    placeholderText: qsTr("Controller name")
                }
            }

            ILConfigurationStep {
                Layout.fillWidth: true
                Layout.rightMargin: 20
                Layout.leftMargin: 20
                stepLine.anchors.bottomMargin: -32
                highlighted: true
                stepId: "2"
                title: qsTr("Select controller type")
                info: qsTr("To define properly your controller you have to
select the specific type. <a href=\"\">More details</a>")
            }

            ILConfigurationStep {
                Layout.rightMargin: 20
                Layout.leftMargin: 20
                Layout.fillWidth: true
                stepLine.anchors.bottomMargin: -32
                stepId: "3"
                enabled: false
                title: qsTr("Change the light name")
                info: qsTr("Adding a specific name to the light would
help to distinct them in the future")
            }

            ILConfigurationStep {
                Layout.rightMargin: 20
                Layout.leftMargin: 20
                Layout.fillWidth: true
                stepLine.visible: false
                stepId: "4"
                enabled: false
                title: qsTr("Select the room")
                info: qsTr("Select the room which will be associated with
this light. You can always change this later.")

            }
        }
    }

    ILToolButton {
        width: 16
        height: 16
        anchors.rightMargin: 18
        anchors.topMargin: 10
        anchors.top: parent.top
        anchors.right: parent.right
        padding: 0
        icon.source: "../../Images/Icon-16-Cancel.svg"
        onClicked: {
            console.log("canceled")
            root.canceled()
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
