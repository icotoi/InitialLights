import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "Controls"
import "Images"

Item {
    id: root
    signal done()

    ColumnLayout {
        id: rowLayout
        anchors.fill: parent

        Button {
            id: skipButton
            text: qsTr("Skip")
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            onClicked: root.done()
        }

        SwipeView {
            id: swipeView
            Layout.fillHeight: true
            Layout.fillWidth: true

            ILOnboardingItem {
                image: "Images/onboarding1.jpg"
                title: "All the lights in a single place"
                message: "With Initial Lights you have all your rooms and their lights in one single app."
            }

            ILOnboardingItem {
                image: "Images/onboarding2.jpg"
                title: "Smart scenes"
                message: "You can easily dim lights, change colours and even create right scenes."
            }

            ILOnboardingItem {
                image: "Images/onboarding3.jpg"
                title: "Multiple setups"
                message: "Your rooms with scenes can ..."
            }
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
