pragma Singleton

import QtQuick 2.12

QtObject {
    id: root

    property color windowBackground: "#303030"
    property color textColor: "#fbfbfb"

    property color borderColor: "#b0b0b0"

    // ILToggleLightButton
    property QtObject toggleLedButton: QtObject {
        property int labelVerticalOffset: -3

        property int ledVerticalMargin: 3
        property int letHorizontalMargin: 3
        property int ledHeight: 5
        property int ledRadius: 2

        property color backgroundDownColor: "#707070"
        property color backgroundHoveredColor: "#626262"
        property color backgroundDefaultColor: "#505050"

        property color dropShadowColor: "#202020"
    }

    // ILColorWheel
    property QtObject colorWheel: QtObject {
        property color borderColor: root.borderColor
    }

    // ILCircularToggleLedButton
    property QtObject circularToggleLedButton: QtObject {
        property color borderColor: root.borderColor
    }
}
