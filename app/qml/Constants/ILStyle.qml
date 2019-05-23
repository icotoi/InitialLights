pragma Singleton

import QtQuick 2.12

QtObject {
    property color windowBackground: "#303030"
    property color textColor: "#fbfbfb"

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
}
