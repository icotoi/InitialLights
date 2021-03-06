import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.12

import "Images"
import "Controls"
import "Constants"

import InitialLights 1.0

Item {
    id: root

    property var controller: null
    property var stack: null

    property string title: controller !== null
                           ? (controller.name !== ""
                              ? controller.name
                              : controller.address)
                           : "(controller)"
    property string message: controller !== null
                             ? controller.message
                             : ""

    signal updateMainToolbar()

    onControllerChanged: {
        if (controller !== null && controller.lights.count === 0) {
            controller.connectToController()
        }
    }

    Component {
        id: colorSelectionView
        PageColorSelection {
            property var light: null
            Component.onDestruction: {
                if (light !== null) {
                    light.color = selectedColor
                }
            }
        }
    }

    ListView {
        id: listView
        anchors.fill: parent

        model: root.controller !== null ? root.controller.lights : null

        delegate: ILLight {
            width: listView.width
            isControllerNameVisible: false
            light: listView.model.get(index)

            onColorSwatchClicked: {
                if (root.stack === null)
                    return;

                root.stack.push(colorSelectionView, { inputColor: color, light: listView.model.get(index) })
                root.updateMainToolbar()
            }
        }
    }

    BusyIndicator {
        id: busyIndicator
        anchors.centerIn: parent
        visible: root.controller !== null && root.controller.isBusy
    }

    Label {
        visible: root.message !== ""
        text: root.message
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        horizontalAlignment: Text.AlignHCenter

        background: Rectangle {
            color: "black"
            opacity: 0.2
        }
    }
}
