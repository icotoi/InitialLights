import QtQuick 2.12
import QtQuick.Controls 2.12

import "../Constants"

ToolButton {
    id: control

    icon.source: "../Images/Icon-16-Arrow-Right.svg"
    icon.height: 16
    icon.width: 16

    implicitHeight: ILStyle.toolbarHeight
    implicitWidth: implicitHeight

    background: Rectangle {
        color: "#0D000000"
        visible: control.down
    }
}
