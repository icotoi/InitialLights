import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0

import "../Constants"

Button {
    id: control

    text: qsTr("Button")
    font: flat ? ILStyle.flatButtonTextFont : ILStyle.defaultButtonTextFont

    property color textColor: flat
                              ? ILStyle.flatButtonTextColor
                              : (highlighted ? ILStyle.highlighteButtonTextColor : ILStyle.defaultButtonTextColor)

    property color borderColor: highlighted ? ILStyle.highlightedButtonBorderColor : ILStyle.defaultButtonBorderColor

    property bool backgroundVisible: !flat
    property color backgroundColor: highlighted ? ILStyle.highlightedButtonBackgroundColor : ILStyle.defaultButtonBackgroundColor
    property int backgroundImplicitWidth: !flat ? 100 : 0
    property int backgroundImplicitHeight: !flat ? ILStyle.buttonImplicitHeight : 0

    property bool dropShadowVisible: enabled && !down && !flat
    property color dropShadowColor: highlighted ? ILStyle.highlightedButtonShadowColor : ILStyle.defaultButtonShadowColor

    contentItem: Text {
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.3
        color: textColor
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight

    }

    background: Rectangle {
        visible: backgroundVisible
        implicitWidth: backgroundImplicitWidth
        implicitHeight: backgroundImplicitHeight
        opacity: enabled ? 1 : 0.3
        border.color: borderColor
        color: backgroundColor
        border.width: 1
        radius: height * 0.5

        // button drop shadow when button not pressed
        layer.enabled: dropShadowVisible
        layer.effect: DropShadow {
            verticalOffset: 1
            color: dropShadowColor
            samples: 9
            radius: 4
        }
    }
}


