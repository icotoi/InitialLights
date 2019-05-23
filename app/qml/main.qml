import QtQuick 2.12
import QtQuick.Controls 2.5

import "Constants"

ApplicationWindow {
    visible: true
    width: 360
    height: 640
    color: ILStyle.windowBackground
    title: qsTr("Hello World")

    Text {
        text: qsTr("text")
        anchors.centerIn: parent
        color: ILStyle.textColor
    }
}
