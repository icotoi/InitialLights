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

    ListView {
        anchors.fill: parent

        model: lightControllers.controllers

        delegate: Item {
            height: 60
            ColumnLayout {
                Label {
                    text: "<b>Name:</b> " + info.name
                }
                Label {
                    text: "<b>Address:</b> " + info.address
                }
            }
        }

        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        focus: true
    }

    BusyIndicator {
        id: busyIndicator
        anchors.centerIn: parent
        visible: lightControllers.scanning
    }

    Label {
        id: messageLabel
        visible: lightControllers.message !== ""
        text: lightControllers.message
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
