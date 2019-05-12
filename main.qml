import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.0

ApplicationWindow {
    visible: true
    width: 720
    height: 1280
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

        LightsMoveForm {

        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        contentHeight: 50

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
            text: qsTr("0-10V")
        }
        TabButton {
            text: qsTr("RGB")
        }
        TabButton {
            text: qsTr("Move Light")
        }
    }
}
