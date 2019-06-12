import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.12

PageDrawerForm {
    property var rooms: undefined

    Material.theme: Material.Light
    backgroundColor: Material.accentColor

    signal homeClicked()
    signal roomClicked(var room)
    signal settingsClicked()

    homeMenu.onClicked: homeClicked()

    roomsRepeater {
        model: rooms
        delegate: MenuItem {
            Layout.fillWidth: true
            text: name
            onClicked: roomClicked(model)
        }
    }

    scenesRepeater {
        model: ListModel {
            ListElement { name: "Scene 1" }
            ListElement { name: "Scene 2" }
            ListElement { name: "Scene 3" }
        }
        delegate: MenuItem {
            enabled: false
            Layout.fillWidth: true
            text: name
        }
    }

    settingsMenu.onClicked: settingsClicked()
}
