import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "Images"
import "Controls"
import "Constants"

Item {
    id: element
    property alias roomView: roomView
    property alias lightView: lightView
    clip: true

    ILRoomView {
        id: roomView

        y: 0
        width: 330
        height: 330
        anchors.horizontalCenter: parent.horizontalCenter
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

        image: "Images/pixabay_illumination-lights-bulbs-731494_1920.jpg"
    }

    ILLight {
        id: lightView
        width: parent.width
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        rgbSlidersVisible: false
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
