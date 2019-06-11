import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

ApplicationWindow {
    id: window
    visible: true
    width: 360
    height: 640
    title: qsTr("BLE demo")

    header: ToolBar {
        id: toolBar
        anchors.right: parent.right
        anchors.left: parent.left
        RowLayout {
            anchors.fill: parent
            ToolButton {
                icon.source: enabled ? "images/material.io--baseline-arrow_back-24px.svg" : ""
                enabled: stackView.depth > 1
                onClicked: stackView.pop()
            }

            Label {
                text: "BLE demo"
                horizontalAlignment: Text.AlignHCenter
                Layout.fillWidth: true
            }

            ToolButton {
                onClicked: lightControllers.scan()
                enabled: !lightControllers.scanning
                icon.source: "images/material.io--baseline-bluetooth_searching-24px.svg"
            }
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: controllersListView
    }

    Component {
        id: controllersListView

        ControllerListView {
            model: lightControllers.controllers
            busy: lightControllers.scanning
            message: lightControllers.message
            onShowController: stackView.push(controllerView, { controller: lightControllers.controllers.get(index) })
        }
    }

    Component {
        id: controllerView
        ControllerView {}
    }
}
