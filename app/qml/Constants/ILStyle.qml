pragma Singleton

import QtQuick 2.12

//    family: "Inter"
//    style: "Bold Italic" "9 10 11 12 13 14 18 24 36 48 64 72 96 144 288"
//    style: "Bold" "9 10 11 12 13 14 18 24 36 48 64 72 96 144 288"
//    style: "Black" "9 10 11 12 13 14 18 24 36 48 64 72 96 144 288"
//    style: "Medium Italic" "9 10 11 12 13 14 18 24 36 48 64 72 96 144 288"
//    style: "Light BETA" "9 10 11 12 13 14 18 24 36 48 64 72 96 144 288"
//    style: "Thin Italic BETA" "9 10 11 12 13 14 18 24 36 48 64 72 96 144 288"
//    style: "Extra Light BETA" "9 10 11 12 13 14 18 24 36 48 64 72 96 144 288"
//    style: "Black Italic" "9 10 11 12 13 14 18 24 36 48 64 72 96 144 288"
//    style: "Semi Bold" "9 10 11 12 13 14 18 24 36 48 64 72 96 144 288"
//    style: "Medium" "9 10 11 12 13 14 18 24 36 48 64 72 96 144 288"
//    style: "Light Italic BETA" "9 10 11 12 13 14 18 24 36 48 64 72 96 144 288"
//    style: "Regular" "9 10 11 12 13 14 18 24 36 48 64 72 96 144 288"
//    style: "Italic" "9 10 11 12 13 14 18 24 36 48 64 72 96 144 288"
//    style: "Semi Bold Italic" "9 10 11 12 13 14 18 24 36 48 64 72 96 144 288"
//    style: "Thin BETA" "9 10 11 12 13 14 18 24 36 48 64 72 96 144 288"
//    style: "Extra Bold" "9 10 11 12 13 14 18 24 36 48 64 72 96 144 288"
//    style: "Extra Bold Italic" "9 10 11 12 13 14 18 24 36 48 64 72 96 144 288"
//    style: "Extra Light Italic BETA" "9 10 11 12 13 14 18 24 36 48 64 72 96 144 288"

QtObject {
    id: root

    enum TextSize {
        Large,
        Medium,
        Small
    }

    property color backgroundColor: "#F3F4F5"
    property color defaultActionableItemColor: "#056CF9"
    property color defaultShadowColor: "#80000000"

    property color titleTextColor: "#17191D"
    property font largeTitleTextFont: Qt.font({ family: "Inter", styleName: "Bold", pointSize: 24 })
    property font mediumTitleTextFont: Qt.font({ family: "Inter", styleName: "Bold", pointSize: 20 })
    property font smallTitleTextFont: Qt.font({ family: "Inter", styleName: "Bold", pointSize: 16 })
    property real titleTextLineHeight: 1.15

    property color infoTextColor: "#5C6670"
    property font largeInfoTextFont: Qt.font({ family: "Inter", styleName: "Regular", pointSize: 18 })
    property font mediumInfoTextFont: Qt.font({ family: "Inter", styleName: "Regular", pointSize: 16 })
    property font smallInfoTextFont: Qt.font({ family: "Inter", styleName: "Medium", pointSize: 12 })

    property font smallTextFont: Qt.font({ family: "Inter", styleName: "Medium", pointSize: 11 })
    property color smallTextColor: "#8F99A3"
    property color smallTextLinkColor: "#3889FA"

    // ILTextField

    property int textFieldImplicitHeight: 56
    property int textFieldTextPaddingHasText: 20

    property color textFieldColor: "#292C33"
    property font textFieldFont: Qt.font({ family: "Inter", styleName: "Medium", pointSize: 16 })

    property color textFieldPlaceholderTextColor: "#ACB4BF"

    property font textFieldSmallPlaceholderTextFont: Qt.font({ family: "Inter", styleName: "Regular", pointSize: 10 })
    property int textFieldSmallPlaceholderTopPadding: 8

    property color textFieldBorderColor: "#DFE1E6"
    property int textFieldBorderRadius: 4

    property color textFieldBackgroundFocus: "#0A0080FF"
    property color textFieldBorderColorFocus: defaultActionableItemColor

    property color textFieldColorInvalid: "#F21F0B"
    property color textFieldBackgroundFocusInvalid: "#FEF2F1"
    property color textFieldBorderColorInvalid: "#FFA299"
    property color textFieldBorderColorFocusInvalid: "#FFA299"
    property font textFieldErrorTextFont: Qt.font({ family: "Inter", styleName: "Medium", pointSize: 12 })

    // ILToolBar styling
    property int toolbarHeight: 48
    property color toolbarBackgroundColor: backgroundColor
    property color toolbarShadowColor: "#0D17191D"

    property font toolbarTitleFont: Qt.font({ family: "Inter", styleName: "Bold", pointSize: 14 })
    property color toolbarTitleColor: infoTextColor

    // ILButton styling
    property int buttonImplicitHeight: 48

    property font flatButtonTextFont: Qt.font({ family: "Inter", styleName: "Medium", pointSize: 16 })
    property font defaultButtonTextFont: Qt.font({ family: "Inter", styleName: "Medium", pointSize: 18 })

    property color flatButtonTextColor: defaultActionableItemColor
    property color highlighteButtonTextColor: "#FFFFFF"
    property color defaultButtonTextColor: defaultActionableItemColor

    property color highlightedButtonBackgroundColor: defaultActionableItemColor
    property color defaultButtonBackgroundColor: "#F1F8FF"

    property color highlightedButtonBorderColor: defaultActionableItemColor
    property color defaultButtonBorderColor: defaultActionableItemColor

    property color highlightedButtonShadowColor: defaultShadowColor
    property color defaultButtonShadowColor: defaultShadowColor
}
