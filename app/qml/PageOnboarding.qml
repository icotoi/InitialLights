import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "Controls"
import "Images"

Item {
    id: root
    signal done()

    property int itemHorizontalMargin: 20

    SwipeView {
        id: swipeView
        anchors.fill: parent

        ILOnboardingItem {
            image: "Images/onboarding1.jpg"
            title: "All your lights are now in one single place"
            message: "With Initial Lights you have all your rooms and their lights connected in one single app."
            textHorizontalMargin: itemHorizontalMargin
        }

        ILOnboardingItem {
            image: "Images/onboarding2.jpg"
            title: "Eco-friendly with our scenes and schedules"
            message: "You can reduce the electricity consumption by using Scenes and Smart Schedules."
            textHorizontalMargin: itemHorizontalMargin
        }

        ILOnboardingItem {
            image: "Images/onboarding3.jpg"
            title: "Easy monitor everything with remote control"
            message: "You can easy check now if your lights are On even when you are away from home."
            textHorizontalMargin: itemHorizontalMargin
        }
    }

    ColumnLayout {
        id: rowLayout
        anchors.rightMargin: itemHorizontalMargin
        anchors.leftMargin: itemHorizontalMargin
        anchors.bottomMargin: 10
        anchors.topMargin: itemHorizontalMargin
        anchors.fill: parent

        ILButton {
            id: skipButton
            flat: true
            text: qsTr("Skip")
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            onClicked: root.done()
        }

        Item { Layout.fillHeight: true}

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

/*##^##
Designer {
    D{i:0;autoSize:true;height:640;width:360}
}
##^##*/
