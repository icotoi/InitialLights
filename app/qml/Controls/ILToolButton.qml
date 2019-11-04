import QtQuick 2.12
import QtQuick.Controls 2.12

import "../Constants"

ToolButton {
    id: control

    implicitHeight: ILStyle.toolbarHeight
    implicitWidth: implicitHeight

    background: Rectangle {
        color: "#0D000000"
        visible: control.down
    }
}
