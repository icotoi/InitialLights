import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../Constants"
import "../Controls"

Page {
    id: root

    implicitWidth: 360
    implicitHeight: 640

    property var stackView

    background: Rectangle {
        color: ILStyle.backgroundColor
    }

    Text {
        text: "Main Page"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
}
