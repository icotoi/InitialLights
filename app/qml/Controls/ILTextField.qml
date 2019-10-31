import QtQuick 2.12
import QtQuick.Controls 2.12

import "../Constants"

TextField {
    id: control

    placeholderText: "Placeholder"

    Text {
        text: control.placeholderText
        color: control.placeholderTextColor
        font: ILStyle.textFieldSmallPlaceholderTextFont
        visible: control.text !== ""
        x: control.leftPadding
        y: ILStyle.textFieldSmallPlaceholderTopPadding
    }

    placeholderTextColor: ILStyle.textFieldPlaceholderTextColor

    color: ILStyle.textFieldColor
    font: ILStyle.textFieldFont

    topPadding: text !== "" ? ILStyle.textFieldTextPaddingHasText : control.bottomPadding
    background: Rectangle {
        implicitWidth: 200
        implicitHeight: ILStyle.textFieldImplicitHeight
        color: control.activeFocus ? ILStyle.textFieldBackgroundFocus : "transparent"
        border.color: control.activeFocus ? ILStyle.textFieldBorderColorFocus : ILStyle.textFieldBoderColor
        radius: ILStyle.textFieldBorderRadius
    }
}
