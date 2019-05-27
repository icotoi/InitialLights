import QtQuick 2.12
import QtQuick.Layouts 1.12

import "Controls"
import "Constants"

P1MainForm {

    topGridLayout.children: [
        // row 1
        ILToggleLedButton {
            text: "Living Room"
            ledColor: "skyblue"
            Layout.fillWidth: true
        },

        ILToggleLedButton {
            text: qsTr("Bedroom")
            ledColor: "tomato"
            Layout.fillWidth: true
        },

        ILToggleLedButton {
            text: qsTr("Bathroom")
            ledColor: "pink"
            Layout.fillWidth: true
        },

        // row 2
        ILToggleLedButton {
            text: qsTr("Kitchen")
            ledColor: "coral"
            Layout.fillWidth: true
            checked: true
        },

        ILToggleLedButton {
            text: qsTr("room")
            ledColor: "greenyellow"
            Layout.fillWidth: true
            checked: true
        },

        ILToggleLedButton {
            text: "Testroom1"
            ledColor: "lemonchiffon"
            Layout.fillWidth: true
            checked: true
        }
    ]

    bottomGridLayout.children: [
        // row 1
        ILToggleLedButton {
            text: qsTr("Coming in")
            ledColor: "pink"
            Layout.fillWidth: true
        },

        ILToggleLedButton {
            text: qsTr("Leave")
            ledColor: "tomato"
            Layout.fillWidth: true
        },

        ILToggleLedButton {
            text: "Garden"
            ledColor: "skyblue"
            Layout.fillWidth: true
        },

        // row 2
        ILToggleLedButton {
            text: qsTr("Stairway")
            ledColor: "coral"
            Layout.fillWidth: true
            checked: true
        },

        ILToggleLedButton {
            text: qsTr("Event")
            ledColor: "greenyellow"
            Layout.fillWidth: true
            checked: true
        },

        ILToggleLedButton {
            text: "Event"
            ledColor: "lemonchiffon"
            Layout.fillWidth: true
            checked: true
        }
    ]
}
