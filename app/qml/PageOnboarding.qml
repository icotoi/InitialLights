import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "Controls"
import "Images"

Item {
    id: root
    signal done()

    SwipeView {
        id: swipeView
        anchors.fill: parent

        ILOnboardingItem {
            image: "Images/onboarding1.jpg"
            title: "All the lights are now in one single place"
            message: "With Initial Lights you have all your rooms and their lights connected in one single app."
        }

        ILOnboardingItem {
            image: "Images/onboarding2.jpg"
            title: "Eco-friendly with our scenes and schedules"
            message: "You can reduce the electricity consumption by using Scenes and Smart Schedules."
        }

        ILOnboardingItem {
            image: "Images/onboarding3.jpg"
            title: "Easy monitor everything with remote control"
            message: "You can easy check now if your lights are On even when you are away from home."
        }
    }

    ColumnLayout {
        id: rowLayout
        anchors.fill: parent

        ILSecondaryButton {
            id: skipButton
            text: qsTr("Skip")
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            onClicked: root.done()
        }

        PageIndicator {
            id: pageIndicator
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            count: swipeView.count
            currentIndex: swipeView.currentIndex
        }

        Button {
            id: nextButton
            text: qsTr("Next")
            Layout.fillWidth: true
            onClicked: if (swipeView.currentIndex == swipeView.count - 1) {
                           root.done()
                       } else {
                           swipeView.currentIndex += 1
                       }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
