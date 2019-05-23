import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtGraphicalEffects 1.12

import "../Constants"

Button {
    id: control

    checkable: true

    text: "Button"
    font.capitalization: Font.MixedCase
    font.bold: true

    property color ledColor: "yellow"

    contentItem: Label {
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.3
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: ILStyle.toggleLedButton.labelVerticalOffset
    }

    background: Item {
        implicitWidth: 100
        implicitHeight: 40
        opacity: enabled ? 1 : 0.3

        Rectangle {
            id: buttonRect
            anchors.fill: parent
            radius: 2
            color: control.down
                   ? ILStyle.toggleLedButton.backgroundDownColor
                   : control.hovered
                     ? ILStyle.toggleLedButton.backgroundHoveredColor
                     : ILStyle.toggleLedButton.backgroundDefaultColor

            Rectangle {
                id: ledRect
                anchors {
                    left: parent.left
                    right: parent.right
                    leftMargin: ILStyle.toggleLedButton.letHorizontalMargin
                    rightMargin: ILStyle.toggleLedButton.letHorizontalMargin
                    bottom: parent.bottom
                    bottomMargin: ILStyle.toggleLedButton.ledVerticalMargin
                }

                height: ILStyle.toggleLedButton.ledHeight
                radius: ILStyle.toggleLedButton.ledRadius
                color: control.checked ? control.ledColor : Qt.darker(control.ledColor, 3)
            }
        }

        DropShadow {
            source: buttonRect
            anchors.fill: buttonRect
            color: ILStyle.toggleLedButton.dropShadowColor
            verticalOffset: control.down ? 2 : 1
            radius: control.down ? 8 : 2
            samples: 12
        }
    }
}
