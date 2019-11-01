import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../Constants"

ColumnLayout {
    id: control

    property alias textField: textField
    property string placeholderText: "Placeholder"
    property bool isValid: errorText == ""
    property string errorText: ""

    TextField {
        id: textField

        Layout.fillWidth: true
        placeholderText: activeFocus ? "" : control.placeholderText
        placeholderTextColor: ILStyle.textFieldPlaceholderTextColor
        color: isValid ? ILStyle.textFieldColor : ILStyle.textFieldColorInvalid
        font: ILStyle.textFieldFont
        topPadding: smallPlaceholderText.visible ? ILStyle.textFieldTextPaddingHasText : textField.bottomPadding

        Text {
            id: smallPlaceholderText
            text: control.placeholderText
            color: textField.placeholderTextColor
            font: ILStyle.textFieldSmallPlaceholderTextFont
            visible: textField.activeFocus || textField.text != ""
            x: textField.leftPadding
            y: ILStyle.textFieldSmallPlaceholderTopPadding
        }

        background: Rectangle {
            implicitWidth: 200
            implicitHeight: ILStyle.textFieldImplicitHeight
            color: textField.activeFocus
                   ? (isValid ? ILStyle.textFieldBackgroundFocus : ILStyle.textFieldBackgroundFocusInvalid)
                   : "transparent"
            border.color: textField.activeFocus
                          ? (isValid ? ILStyle.textFieldBorderColorFocus : ILStyle.textFieldBorderColorFocusInvalid)
                          : (isValid ? ILStyle.textFieldBorderColor : ILStyle.textFieldBorderColorInvalid)
            radius: ILStyle.textFieldBorderRadius
        }
    }

    Text {
        text: errorText
        visible: text != ""
        color: ILStyle.textFieldColorInvalid
        font: ILStyle.textFieldErrorTextFont
    }
}
