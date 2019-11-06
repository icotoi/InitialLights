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

    Component {
        id: registerNewUserView
        PageRegisterNewUser {
            user: root.user
            onRegisterNewUser: {
                if (stackView && user && user.registerNewUser(email, password)) {
                    stackView.replace(userRegisteredView)
                }
            }
            onBack: stackView.pop()
        }
    }

    Component {
        id: userRegisteredView
        PageUserRegistered {
            onDone: stackView.pop(StackView.ReplaceTransition)
        }
    }

    Component {
        id: loginView
        PageLogin {
            user: root.user
            onBack: stackView.pop()
            onLogin: user.login(email, password)
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
            onClicked: stackView.push(registerNewUserView)
        }

        ILButton {
            text: qsTr("Login")
            backgroundColor: "transparent"
            dropShadowVisible: false
            Layout.topMargin: 11
            Layout.fillWidth: true
            onClicked: stackView.push(loginView)
        }

        ILButton {
            flat: true
            text: qsTr("Forgot your password?")
            Layout.topMargin: 16
            Layout.fillWidth: true
            onClicked: {} // TODO
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
