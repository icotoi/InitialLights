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

        P1Main {

        }

        DemoColorWheel {
        }

        DemoToggleLedButton {
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton {
            text: qsTr("Main")
        }

        TabButton {
            text: qsTr("Color Wheel")
        }

        TabButton {
            text: qsTr("Buttons")
        }
    }
}
