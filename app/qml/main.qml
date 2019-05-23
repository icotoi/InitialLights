import QtQuick 2.12
import QtQuick.Controls 2.5

ApplicationWindow {
    visible: true
    width: 360
    height: 640
    title: qsTr("Initial Lights")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page {
            Label {
                text: qsTr("Main")
                anchors.centerIn: parent
            }
        }

        Page {
            Label {
                text: qsTr("Room")
                anchors.centerIn: parent
            }
        }

        Page {
            Label {
                text: qsTr("4PWM")
                anchors.centerIn: parent
            }
        }

        Page {
            Label {
                text: qsTr("0-10V")
                anchors.centerIn: parent
            }
        }

        Page {
            Label {
                text: qsTr("RGB")
                anchors.centerIn: parent
            }
        }

        Page {
            Label {
                text: qsTr("Move Light")
                anchors.centerIn: parent
            }
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
