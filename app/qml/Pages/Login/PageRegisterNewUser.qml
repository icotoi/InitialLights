import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../../Constants"
import "../../Controls"

import QtGraphicalEffects 1.0

Page {
    id: root

    implicitWidth: 360
    implicitHeight: 640

    property var stackView

    function back() {
        if (stackView)
            stackView.pop()
    }

    background: Rectangle {
        color: ILStyle.backgroundColor
    }

    header: ILToolBar {
        ILToolBarBackButton {
            onClicked: back()
        }

        ILToolBarTitle {
            text: qsTr("Register")
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
            placeholderText: qsTr("Email address")
            Layout.fillWidth: true
        }

        ILTextField {
            Layout.fillWidth: true
            placeholderText: qsTr("Password")
            echoMode: TextInput.Password
        }

        ILTextField {
            Layout.fillWidth: true
            placeholderText: qsTr("Confirm password")
            echoMode: TextInput.Password
        }

        ILButton {
            text: qsTr("Create your account")
            Layout.topMargin: 6
            Layout.fillWidth: true
            highlighted: true

        }
    }

    Text {
        text: qsTr(
                  "<style>"
                  + "a { text-decoration:none; color: %1}".arg(ILStyle.smallTextLinkColor)
                  + "</style>"
                  + "By proceeding, you are confirming that you have read and accepted the "
                  + "<a href=\"https://en.wikipedia.org/wiki/End-user_license_agreement\">End User License Agreement (EULA)</a>,"
                  + " the <a href=\"https://en.wikipedia.org/wiki/Contractual_term\">Terms and Conditions</a>"
                  + " and our <a href=\"https://en.wikipedia.org/wiki/Privacy_policy\">Privacy Policy</a>")
        textFormat: Text.RichText
        horizontalAlignment: Text.AlignHCenter
        anchors.bottomMargin: 20
        anchors.rightMargin: 20
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.bottom: parent.bottom
        wrapMode: Text.WordWrap
        font: ILStyle.smallTextFont
        color: ILStyle.smallTextColor
        lineHeight: 1.3
        onLinkActivated: Qt.openUrlExternally(link)
    }

}
