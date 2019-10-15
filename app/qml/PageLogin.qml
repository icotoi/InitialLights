import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import "Controls"

Item {
    id: root

    property int margin: 20

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
                text: qsTr("Log in")
            }

            TextField {
                Layout.fillWidth: true
                placeholderText: qsTr("Email")
            }

            TextField {
                Layout.fillWidth: true
                placeholderText: qsTr("Password")
            }

            RowLayout {
                Layout.fillWidth: true
                ILSecondaryButton {
                    text: qsTr("New account")
                    Layout.fillWidth: true
                }

                ILSecondaryButton {
                    text: qsTr("Forgot password?")
                    Layout.fillWidth: true
                }
            }
        }
    }

    Button {
        y: 216
        text: qsTr("Log in")
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
    D{i:0;autoSize:true;height:480;width:640}D{i:1;anchors_x:0;anchors_y:5}D{i:9;anchors_x:0}
}
##^##*/
