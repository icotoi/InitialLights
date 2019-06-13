import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.12

PageDrawerForm {
    property var rooms: null
    property var scenes: null

    Material.theme: Material.Light
    backgroundColor: Material.accentColor

    signal roomClicked(var room)

    roomsRepeater {
        model: rooms
        delegate: MenuItem {
            Layout.fillWidth: true
            text: name
            onClicked: roomClicked(model)
        }
    }

    scenesRepeater {
        model: scenes
        delegate: MenuItem {
            enabled: false
            Layout.fillWidth: true
            text: name
        }
    }
}
