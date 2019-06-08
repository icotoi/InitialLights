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
            Label {
                text: "BLE demo"
            }
            ToolButton {
                text: "Scan"
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

