import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "Images"
import "Controls"
import "Constants"

Item {
    id: element

    property alias controllerList: controllerList
    property alias channelList: channelList
    property alias clearLocalData: clearLocalData

    ColumnLayout {
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top

        Button {
            id: controllerList
            text: qsTr("Controllers")
            flat: true
            Layout.fillWidth: true
            icon.source: ILStyle.controllersIconSource
        }

        Button {
            id: channelList
            text: qsTr("Channels")
            flat: true
            Layout.fillWidth: true
            icon.source: ILStyle.channelsIconSource
        }

        Button {
            id: clearLocalData
            text: qsTr("Clear Local Data")
            flat: true
            Layout.fillWidth: true
            icon.source: ILStyle.clearLocalDataIconSource
        }
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
