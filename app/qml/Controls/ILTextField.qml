import QtQuick 2.12
import QtQuick.Controls 2.12

import "../Constants"

TextField {
    id: control

    property string extraPlaceholderText: "Placeholder"

    placeholderText: activeFocus ? "" : extraPlaceholderText

    Text {
        text: control.extraPlaceholderText
        color: control.placeholderTextColor
        font: ILStyle.textFieldSmallPlaceholderTextFont
        visible: control.activeFocus
        x: control.leftPadding
        y: ILStyle.textFieldSmallPlaceholderTopPadding
    }

    placeholderTextColor: ILStyle.textFieldPlaceholderTextColor

    color: ILStyle.textFieldColor
    font: ILStyle.textFieldFont

    topPadding: control.activeFocus ? ILStyle.textFieldTextPaddingHasText : control.bottomPadding
    background: Rectangle {
        implicitWidth: 200
        implicitHeight: ILStyle.textFieldImplicitHeight
        color: control.activeFocus ? ILStyle.textFieldBackgroundFocus : "transparent"
        border.color: control.activeFocus ? ILStyle.textFieldBorderColorFocus : ILStyle.textFieldBorderColor
        radius: ILStyle.textFieldBorderRadius
    }
}
