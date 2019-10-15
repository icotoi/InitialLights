import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import "Controls"

Item {
    id: root

    property int margin: 20

    signal resetPassword()
    signal registerNewUser()

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
                Layout.fillWidth: true
                placeholderText: qsTr("Full Name")
            }

            TextField {
                Layout.fillWidth: true
                placeholderText: qsTr("Email")
            }

            TextField {
                Layout.fillWidth: true
                placeholderText: qsTr("Password")
            }

            TextField {
                Layout.fillWidth: true
                placeholderText: qsTr("Password")
            }

            TextField {
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
        anchors.right: parent.right
        anchors.rightMargin: root.margin
        anchors.left: parent.left
        anchors.leftMargin: root.margin
        anchors.bottom: parent.bottom
        anchors.bottomMargin: root.margin
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
