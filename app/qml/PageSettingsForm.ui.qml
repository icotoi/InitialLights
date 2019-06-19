import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "Images"
import "Controls"
import "Constants"

Item {
    id: element

    property alias controllerList: controllerList
    property alias lightList: lightList
    property alias clearLocalData: clearLocalData
    property alias reloadDemoData: reloadDemoData
    property alias roomList: roomList

    ColumnLayout {
        spacing: 0
        anchors.fill: parent

        ItemDelegate {
            id: roomList
            text: qsTr("Rooms")
            Layout.fillWidth: true
            icon.source: ILStyle.roomsIconSource
        }

        ItemDelegate {
            id: scenesList
            text: qsTr("Scenes")
            enabled: false
            Layout.fillWidth: true
            icon.source: ILStyle.scenesIconSource
        }

        ItemDelegate {
            id: controllerList
            text: qsTr("Controllers")
            Layout.fillWidth: true
            icon.source: ILStyle.controllersIconSource
        }

        ItemDelegate {
            id: lightList
            text: qsTr("Lights")
            Layout.fillWidth: true
            icon.source: ILStyle.lightsIconSource
        }

        Item {
            Layout.fillHeight: true
        }

        Button {
            id: clearLocalData
            text: qsTr("Clear Local Data")
            flat: true
            Layout.fillWidth: true
            icon.source: ILStyle.clearLocalDataIconSource
        }

        Button {
            id: reloadDemoData
            text: qsTr("Reload Demo Data")
            flat: true
            Layout.fillWidth: true
            icon.source: ILStyle.reloadDemoDataIconSource
        }
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
