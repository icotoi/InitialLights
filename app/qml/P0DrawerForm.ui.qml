import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    property string backgroundColor: "Orange"
    property alias roomsRepeater: roomsRepeater
    property alias settingsMenu: settingsMenu
    property alias homeMenu: homeMenu
    property alias scenesRepeater: scenesRepeater

    Rectangle {
        color: backgroundColor
        anchors.fill: parent
    }

    Flickable {
        id: flickable
        clip: true
        anchors.fill: parent
        contentHeight: mainColumnLayout.height

        ColumnLayout {
            id: mainColumnLayout
            width: flickable.width
            spacing: 0

            MenuItem {
                id: homeMenu
                text: qsTr("Home")
                icon.source: "Images/material.io-sharp-home-24px.svg"
                Layout.fillWidth: true
            }

            MenuSeparator {
                topPadding: 0
                bottomPadding: 0
                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Rooms")
                rightPadding: 8
                font.pointSize: 10
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignRight
            }

            Repeater {
                id: roomsRepeater
            }

            MenuSeparator {
                bottomPadding: 0
                topPadding: 0
                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Scenes")
                rightPadding: 8
                font.pointSize: 10
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignRight
            }

            Repeater {
                id: scenesRepeater
            }

            MenuSeparator {
                bottomPadding: 0
                topPadding: 0
                Layout.fillWidth: true
            }

            MenuItem {
                id: settingsMenu
                text: "Settings"
                Layout.fillWidth: true
                icon.source: "Images/material.io-sharp-settings-24px.svg"
            }
        }
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:1;invisible:true}
}
 ##^##*/
