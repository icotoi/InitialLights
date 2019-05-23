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
        ILToggleLedButton {
            text: qsTr("Bathroom")
            ledColor: "#ff8800"
            Layout.fillWidth: true
        }

        ILToggleLedButton {
            text: qsTr("Bedroom")
            Layout.fillWidth: true
        }

        ILToggleLedButton {
            text: "Living Room"
            ledColor: "#ff0088"
            Layout.fillWidth: true
        }

        // row 2
        ILToggleLedButton {
            text: qsTr("Bathroom")
            ledColor: "#ff8800"
            Layout.fillWidth: true
            checked: true
        }

        ILToggleLedButton {
            text: qsTr("Bedroom")
            Layout.fillWidth: true
            checked: true
        }

        ILToggleLedButton {
            text: "Living Room"
            ledColor: "#ff0088"
            Layout.fillWidth: true
            checked: true
        }

        // row 3
        ILToggleLedButton {
            text: qsTr("Bathroom")
            ledColor: "#ff8800"
            Layout.fillWidth: true
            enabled: false
        }

        ILToggleLedButton {
            text: qsTr("Bedroom")
            Layout.fillWidth: true
            enabled: false
        }

        ILToggleLedButton {
            text: "Living Room"
            ledColor: "#ff0088"
            Layout.fillWidth: true
            enabled: false
        }

        // row 4
        ILToggleLedButton {
            text: qsTr("Bathroom")
            ledColor: "#ff8800"
            Layout.fillWidth: true
            enabled: false
            checked: true
        }

        ILToggleLedButton {
            text: qsTr("Bedroom")
            Layout.fillWidth: true
            enabled: false
            checked: true
        }

        ILToggleLedButton {
            text: "Living Room"
            ledColor: "#ff0088"
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
