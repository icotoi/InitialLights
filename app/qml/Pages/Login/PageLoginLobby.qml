import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../../Controls"

Page {
    id: root

    implicitWidth: 360
    implicitHeight: 640

    property var stackView
    property var user

    function login() {}

    function registerNewUser() {
        if (stackView) {
            stackView.push(registerNewUserView)
        }
    }

    function resetPassword() {}

    Component {
        id: registerNewUserView
        PageRegisterNewUser {
            stackView: root.stackView
            user: root.user
        }
    }

    Image {
        id: image
        anchors.fill: parent
        source: "../../Images/background-login-1.jpg"
        fillMode: Image.PreserveAspectCrop
    }

    ColumnLayout {
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.bottomMargin: 34

        ILButton {
            highlighted: true
            text: qsTr("Create a new account")
            Layout.fillWidth: true
            onClicked: registerNewUser()
        }

        ILButton {
            text: qsTr("Login")
            backgroundColor: "transparent"
            dropShadowVisible: false
            Layout.topMargin: 11
            Layout.fillWidth: true
            onClicked: login()
        }

        ILButton {
            flat: true
            text: qsTr("Forgot your password?")
            Layout.topMargin: 16
            Layout.fillWidth: true
            onClicked: resetPassword()
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
