import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../../Constants"
import "../../Controls"

Page {
    id: root

    implicitWidth: 360
    implicitHeight: 640

    property var stackView

    background: Rectangle {
        color: ILStyle.backgroundColor
    }

    header: ILToolBar {
        id: iLToolBar
        ILToolBarTitle {
            text: qsTr("Setup your space")
        }

        ILButton {
            text: qsTr("Next")
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            flat: true
        }
    }

    ColumnLayout {
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        ILTitleText {
            text: qsTr("Your Rooms")
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
        }

        ILInfoText {
            text: qsTr("Start by creating your rooms.<br>This can be done later.")
            Layout.bottomMargin: 20
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
        }

        Repeater {
            model: [ "Living Room", "Kitchen", "", "" ]

            RowLayout {
                id: rowLayout

                ILToolButton {
                    display: AbstractButton.IconOnly
                    icon.source: "../../Images/material.io-remove-24px.svg"
                    icon.width: 32
                    icon.height: 32
                }

                ILTextField {
                    placeholderText: qsTr("Room Name")
                    textField.text: modelData
                }
            }
        }

        ILButton {
            text: qsTr("Add new room")
            Layout.topMargin: 20
            Layout.fillWidth: true
            highlighted: true
        }

    }
}
