import QtQuick 2.12
import QtQuick.Controls 2.12

Button {
    id: control
    text: qsTr("Button")

    font.pointSize: flat ? 14: 18
    font.bold: flat
    font.capitalization: flat ? Font.AllUppercase : Font.MixedCase

    property color borderColor: "#056CF9"
    property color backgroundColorHighlighted: "#056CF9"
    property color backgroundColor: "#F1F8FF"

    property color textColor: "#056CF9"
    property color textColorHighlighted: "#FFF"
    property color textColorFlat: "#000"

    // TODO: check if this is ok or another way of interaction feedback is required
    transform: Translate {
        x: control.down ? 1 : 0
        y: control.down ? 1 : 0
    }

    contentItem: Text {
        text: control.text
        font: control.font
        opacity: flat
                 ? (enabled ? 0.6 : 0.3)
                 : (enabled ? 1.0 : 0.3)
        color: flat
               ? textColorFlat
               : (control.highlighted ? textColorHighlighted : textColor)

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        implicitWidth: flat ? 0 : 100
        implicitHeight: flat ? 0 : 48
        visible: !flat
        opacity: enabled ? 1 : 0.3
        border.color: borderColor
        color: control.highlighted ? backgroundColorHighlighted : backgroundColor
        border.width: 1
        radius: height * 0.5
    }
}

/*##^##
Designer {
    D{i:0;height:44;width:320}
}
##^##*/
