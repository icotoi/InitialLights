import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import "Controls"

Item {
    id: root

    property int margin: 20

    property alias fullName: fullName.text
    property alias user: user.text
    property alias password: password.text

    property bool hasValidInput: fullName.text != "" &&
                                 user.text != "" &&
                                 password.text != "" &&
                                 password.text == passwordConfirmation.text

    signal resetPassword()
    signal registerNewUser()
    signal done()

    ILPane {
        id: pane
        anchors.rightMargin: root.margin
        anchors.leftMargin: root.margin
        anchors.topMargin: root.margin
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.left: parent.left

        ColumnLayout {
            anchors.fill: parent

            ILTitleLabel {
                text: qsTr("Create a new account")
            }

            TextField {
                id: fullName
                Layout.fillWidth: true
                placeholderText: qsTr("Full Name")
            }

            TextField {
                id: user
                Layout.fillWidth: true
                placeholderText: qsTr("Email")
            }

            TextField {
                id: password
                Layout.fillWidth: true
                placeholderText: qsTr("Password")
            }

            TextField {
                id: passwordConfirmation
                Layout.fillWidth: true
                placeholderText: qsTr("Confirm Password")
            }

            ILInfoLabel {
                text: qsTr("By creating an account you agree to our Terms of Service and Privacy Policy")
                wrapMode: Text.WordWrap
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }

    Button {
        text: qsTr("Continue")
        enabled: hasValidInput
        anchors.right: parent.right
        anchors.rightMargin: root.margin
        anchors.left: parent.left
        anchors.leftMargin: root.margin
        anchors.bottom: parent.bottom
        anchors.bottomMargin: root.margin
        onClicked: if (hasValidInput) done()
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
