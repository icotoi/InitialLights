import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "Controls"
import "Constants"

Item {
    id: root
    clip: true

    property color ledColor: "skyblue"
    property string title: qsTr("Initial Lights")

    property alias rooms: roomsRepeater.model
    property alias scenes: scenesRepeater.model
    property alias mainButton: mainButton

    property var extraToolbarItems: [
    ]

    signal roomClicked(int index, bool checked)

    GridLayout {
        id: roomsLayout
        anchors.margins: 20
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        columns: 3

        Repeater {
            id: roomsRepeater
            model: 9
            delegate: ILToggleLedButton {
                text: model.name
                ledColor: root.ledColor
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop
                onClicked: root.roomClicked(index, checked)
            }
        }
    }

    ILMainPowerButton {
        id: mainButton
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 20
        anchors.verticalCenter: parent.verticalCenter
    }

    GridLayout {
        id: scenesLayout
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        columns: 3

        anchors.margins: 20

        Repeater {
            id: scenesRepeater
            model: 8
            delegate: ILToggleLedButton {
                text: qsTr("Scene %1".arg(modelData + 1))
                ledColor: root.ledColor
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignBottom
                enabled: false
            }
        }
    }
}
