import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import "../../Constants"
import "../../Controls"

Page {
    id: root

    implicitWidth: 360
    implicitHeight: 640

    signal back()
    signal next()
    signal scan()

    property var rooms

    background: Rectangle {
        color: ILStyle.backgroundColor
    }

    header: ILToolBar {
        id: iLToolBar

        ILToolBarBackButton {
            onClicked: back()
        }

        ILToolBarTitle {
            text: qsTr("Add your lights")
        }

        ILButton {
            text: qsTr("Next")
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            flat: true
            onClicked: next()
        }
    }

    ColumnLayout {
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        Image {
            id: image
            Layout.bottomMargin: 25
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            source: "../../Images/Illustration-No-Lights-Defined.png"
        }

        ILInfoText {
            text: qsTr("Currently there are\nno lights added")
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }
    }

    ILButton {
        text: qsTr("Scan for lights")
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        highlighted: true
        onClicked: scan()
    }
}
