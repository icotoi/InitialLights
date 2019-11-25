import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0

import "../Constants"

ILButton {
    id: control

    implicitWidth: 150

    property bool busy: false

    BusyIndicator {
        z: 2
        visible: busy
        running: visible
        height: control.height * 0.8
        anchors.rightMargin: (control.height - height) / 2
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        width: height
    }
}
