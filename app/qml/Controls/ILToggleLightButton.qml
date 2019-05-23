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

    property color lightColor: "yellow"

    contentItem: Label {
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.3
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: ILStyle.toggleLightButton.labelVerticalOffset
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
                   ? ILStyle.toggleLightButton.backgroundDownColor
                   : control.hovered
                     ? ILStyle.toggleLightButton.backgroundHoveredColor
                     : ILStyle.toggleLightButton.backgroundDefaultColor

            Rectangle {
                id: ledRect
                anchors {
                    left: parent.left
                    right: parent.right
                    leftMargin: ILStyle.toggleLightButton.letHorizontalMargin
                    rightMargin: ILStyle.toggleLightButton.letHorizontalMargin
                    bottom: parent.bottom
                    bottomMargin: ILStyle.toggleLightButton.ledVerticalMargin
                }

                height: ILStyle.toggleLightButton.ledHeight
                radius: ILStyle.toggleLightButton.ledRadius
                color: control.checked ? control.lightColor : Qt.darker(control.lightColor, 3)
            }
        }

        DropShadow {
            source: buttonRect
            anchors.fill: buttonRect
            color: ILStyle.toggleLightButton.dropShadowColor
            verticalOffset: control.down ? 2 : 1
            radius: control.down ? 8 : 2
            samples: 12
        }
    }
}
