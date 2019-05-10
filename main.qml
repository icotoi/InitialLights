import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Tabs")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        P1MainForm {
        }

        P2RoomForm {
        }

        P34PWMForm {
        }

        P42AnalogForm {
        }

        P5RGBForm {
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton {
            text: qsTr("Main")
        }
        TabButton {
            text: qsTr("Room")
        }
        TabButton {
            text: qsTr("4PWM")
        }
        TabButton {
            text: qsTr("2Analog")
        }
        TabButton {
            text: qsTr("RGB")
        }
    }
}
