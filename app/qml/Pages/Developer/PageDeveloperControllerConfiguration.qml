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
