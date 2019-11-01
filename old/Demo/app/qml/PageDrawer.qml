import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.12

PageDrawerForm {
    property var rooms: null
    property var scenes: null

    Material.theme: Material.Light
    backgroundColor: Material.accentColor

    signal roomClicked(int index)

    roomsRepeater {
        model: rooms
        delegate: ItemDelegate {
            Layout.fillWidth: true
            text: name
            onClicked: roomClicked(index)
        }
    }

    scenesRepeater {
        model: scenes
        delegate: ItemDelegate {
            enabled: false
            visible: false
            Layout.fillWidth: true
            text: name
        }
    }
}
