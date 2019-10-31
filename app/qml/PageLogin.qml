import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "Controls"
import "Images"

Item {
    id: root

    implicitWidth: 360
    implicitHeight: 640

    property int itemHorizontalMargin: 20

    signal login()
    signal registerNewUser()
    signal resetPassword()

    Image {
        id: image
        anchors.fill: parent
        source: "Images/background-login-1.jpg"
        fillMode: Image.PreserveAspectCrop
    }

    ColumnLayout {
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        anchors.rightMargin: itemHorizontalMargin
        anchors.leftMargin: itemHorizontalMargin
        anchors.bottomMargin: itemHorizontalMargin

        ILButton {
            highlighted: true
            text: qsTr("Create a new account")
            Layout.fillWidth: true
            onClicked: registerNewUser()
        }

        ILButton {
//            flat: true
            text: qsTr("Login")
            backgroundColor: "transparent"
            dropShadow: false
            Layout.topMargin: 10
            Layout.fillWidth: true
            onClicked: login()
        }

        ILButton {
            flat: true
            text: qsTr("Forgot your password?")
            Layout.topMargin: 34
            Layout.fillWidth: true
            onClicked: resetPassword()
        }
    }
}

/*##^##
Designer {
    D{i:1;anchors_height:100;anchors_width:100;anchors_x:130;anchors_y:204}
}
##^##*/
