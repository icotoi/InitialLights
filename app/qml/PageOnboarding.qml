import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "Constants"
import "Controls"
import "Images"

Item {
    id: root

    width: 360
    height: 640

    signal done()

    SwipeView {
        id: swipeView
        anchors.fill: parent

        ILOnboardingItem {
            image: "Images/background-onboarding-1.jpg"
            title: "All your lights are now in one single place"
            message: "With Initial Lights you have all your rooms and their lights connected in one single app."
            textHorizontalMargin: 20
        }

        ILOnboardingItem {
            image: "Images/background-onboarding-2.jpg"
            title: "Eco-friendly with our scenes and schedules"
            message: "You can reduce the electricity consumption by using Scenes and Smart Schedules."
            textHorizontalMargin: 20
        }

        ILOnboardingItem {
            image: "Images/background-onboarding-3.jpg"
            title: "Easy monitor everything with remote control"
            message: "You can easy check now if your lights are On even when you are away from home."
            textHorizontalMargin: 20
        }
    }

    ILButton {
        id: skipButton
        flat: true
        text: qsTr("SKIP")
        anchors.top: parent.top
        anchors.topMargin: 48
        anchors.right: parent.right
        anchors.rightMargin: 8
        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
        onClicked: root.done()
        font: ILStyle.flatButtonTextBoldFont
    }

    ColumnLayout {
        id: rowLayout
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.bottomMargin: 10


        ILButton {
            id: nextButton
            text: qsTr("Next")
            highlighted: true
            Layout.fillWidth: true
            onClicked: if (swipeView.currentIndex == swipeView.count - 1) {
                           root.done()
                       } else {
                           swipeView.currentIndex += 1
                       }
        }

        ILPageIndicator {
            id: pageIndicator
            Layout.topMargin: 20
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            count: swipeView.count
            currentIndex: swipeView.currentIndex
        }

    }
}
