import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "Images"
import "Controls"

Item {
    id: element
    width: 360
    height: 590
    clip: true

    Item {
        id: controlContainer
        width: 330
        height: 330
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        Image {
            id: image
            anchors.fill: parent
            fillMode: Image.PreserveAspectFit
            source: "Images/pixabay_illumination-lights-bulbs-731494_1920.jpg"
        }

        ILCircularToggleLedButton {
            id: iLCircularToggleLedButton
            x: 33
            y: 187
            color: "#00ffff"
        }

        ILCircularToggleLedButton {
            id: iLCircularToggleLedButton1
            x: 97
            y: 111
            color: "#ffff00"
        }

        ILCircularToggleLedButton {
            id: iLCircularToggleLedButton2
            x: 119
            y: 201
            color: "#ffffff"
        }
    }
}


















/*##^## Designer {
    D{i:2;anchors_x:108;anchors_y:138}
}
 ##^##*/
