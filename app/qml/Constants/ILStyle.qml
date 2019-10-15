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

    // Color Sampler
    property QtObject colorRectangle: QtObject {
        property int size: 40
        property int radius: 4
        property int borderWidth: 2
        property color borderColor: root.borderColor
    }

    // Icons
    property string hamburgerIconSource: "Images/material.io-baseline-menu-24px.svg"
    property string backIconSource: "Images/material.io-baseline-arrow_back-24px.svg"
    property string homeIconSource: "Images/material.io-sharp-home-24px.svg"
    property string roomsIconSource: "Images/material.io-baseline-location_city-24px.svg"
    property string scenesIconSource: "Images/material.io-baseline-weekend-48px.svg"
    property string settingsIconSource: "Images/material.io-sharp-settings-24px.svg"
    property string controllersIconSource: "Images/material.io-baseline-settings_input_svideo-24px.svg"
    property string lightsIconSource: "Images/material.io-baseline-wb_incandescent-24px.svg"
    property string bluetoothScanIconSource: "Images/material.io-sharp-bluetooth_searching-24px.svg"
    property string logoutIconSource: "Images/fontawesome-user-times.svg"

    property string refreshControllerLightConfigurationSource: "Images/material.io-baseline-refresh-24px.svg"

    property string addIconSource: "Images/material.io-sharp-add-24px.svg"

    property string editIconSource: "Images/material.io-baseline-edit-24px.svg"

    // Demo stuff
    property string clearLocalDataIconSource: "Images/material.io-baseline-delete-24px.svg"
    property string reloadDemoDataIconSource: "Images/material.io-baseline-refresh-24px.svg"
}
