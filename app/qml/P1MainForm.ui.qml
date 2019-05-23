import QtQuick 2.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

import "Controls"
import "Constants"

Item {
    id: element
    width: 400
    height: 400

    GridLayout {
        id: gridLayout
        anchors.rightMargin: 5
        anchors.leftMargin: 5
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.left: parent.left
        columns: 3

        // row 1
        ILToggleLightButton {
            text: qsTr("Bathroom")
            lightColor: "#ff8800"
            Layout.fillWidth: true
        }

        ILToggleLightButton {
            text: qsTr("Bedroom")
            Layout.fillWidth: true
        }

        ILToggleLightButton {
            text: "Living Room"
            lightColor: "#ff0088"
            Layout.fillWidth: true
        }

        // row 2
        ILToggleLightButton {
            text: qsTr("Bathroom")
            lightColor: "#ff8800"
            Layout.fillWidth: true
            checked: true
        }

        ILToggleLightButton {
            text: qsTr("Bedroom")
            Layout.fillWidth: true
            checked: true
        }

        ILToggleLightButton {
            text: "Living Room"
            lightColor: "#ff0088"
            Layout.fillWidth: true
            checked: true
        }

        // row 3
        ILToggleLightButton {
            text: qsTr("Bathroom")
            lightColor: "#ff8800"
            Layout.fillWidth: true
            enabled: false
        }

        ILToggleLightButton {
            text: qsTr("Bedroom")
            Layout.fillWidth: true
            enabled: false
        }

        ILToggleLightButton {
            text: "Living Room"
            lightColor: "#ff0088"
            Layout.fillWidth: true
            enabled: false
        }

        // row 4
        ILToggleLightButton {
            text: qsTr("Bathroom")
            lightColor: "#ff8800"
            Layout.fillWidth: true
            enabled: false
            checked: true
        }

        ILToggleLightButton {
            text: qsTr("Bedroom")
            Layout.fillWidth: true
            enabled: false
            checked: true
        }

        ILToggleLightButton {
            text: "Living Room"
            lightColor: "#ff0088"
            Layout.fillWidth: true
            enabled: false
            checked: true
        }

        // row 5
        Button {
            text: qsTr("Button")
            Layout.fillWidth: true
        }

        Button {
            text: qsTr("Button")
            checkable: true
            Layout.fillWidth: true
        }
    }
}

/*##^## Designer {
    D{i:1;anchors_width:100}
}
 ##^##*/
