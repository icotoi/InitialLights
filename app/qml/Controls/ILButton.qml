import QtQuick 2.12
import QtQuick.Controls 2.12

Button {
    id: control
    text: qsTr("Button")

    property color borderColor: "#056CF9"
    property color backgroundColorHighlighted: "#056CF9"
    property color backgroundColor: "#F1F8FF"

    property color textColor: "#056CF9"
    property color textColorHighlighted: "#FFF"

    // TODO: check if this is ok or another way of interaction feedback is required
    transform: Translate {
        x: control.down ? 1 : 0
        y: control.down ? 1 : 0
    }

    contentItem: Text {
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.3
        color: control.highlighted ? textColorHighlighted : textColor

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        implicitWidth: 100
        implicitHeight: 40
        opacity: enabled ? 1 : 0.3
        border.color: borderColor
        color: control.highlighted ? backgroundColorHighlighted : backgroundColor
        border.width: 1
        radius: height * 0.5
    }
}
