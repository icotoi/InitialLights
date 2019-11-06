import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../../Constants"
import "../../Controls"

Page {
    id: root

    implicitWidth: 360
    implicitHeight: 640

    property var user

    signal back()
    signal login(string email, string password)

    background: Rectangle {
        color: ILStyle.backgroundColor
    }

    header: ILToolBar {
        ILToolBarBackButton {
            onClicked: back()
        }

        ILToolBarTitle {
            text: qsTr("Login")
        }
    }

    ColumnLayout {
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.topMargin: 48
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        spacing: 16

        ILTextField {
            id: emailTextField
            placeholderText: qsTr("Email address")
            Layout.fillWidth: true
        }

        ILTextField {
            id: passwordTextField
            Layout.fillWidth: true
            placeholderText: qsTr("Password")
            textField.echoMode: TextInput.Password
        }

        ILButton {
            text: qsTr("Login")
            Layout.topMargin: 6
            Layout.fillWidth: true
            highlighted: true
            onClicked: {
                errorText.visible = false
                root.login(emailTextField.textField.text, passwordTextField.textField.text)
            }
        }

        Text {
            id: errorText
            text: qsTr("Email address/password do not match")
            color: ILStyle.textFieldColorInvalid
            font: ILStyle.textFieldErrorTextFont
            visible: false
        }
    }

    BusyIndicator {
        id: busyIndicator
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        visible: user && user.isOperationPending
    }

    Connections {
        target: user

        onLoginRequestFinished: {
            if (user && !user.isLogged) {
                errorText.visible = true
            }
        }
    }
}
