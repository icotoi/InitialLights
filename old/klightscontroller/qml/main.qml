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
                icon.source: "images/material.io--baseline-perm_scan_wifi-24px.svg"
            }
        }
    }
}

//        Button {
//            id:call
//            width: 0.75*parent.width
//            height: 0.15*parent.height
//            anchors.centerIn: parent
//            text: "Scan for Devices"
//            onClicked: pageLoader.source="home.qml"
//        }
//    }

//    Loader {
//        id: pageLoader
//        anchors.fill: parent
//    }
//}

