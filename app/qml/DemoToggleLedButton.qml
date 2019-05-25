import QtQuick 2.12
import QtQuick.Layouts 1.3

import "Controls"
import "Constants"


DemoToggleLedButtonForm {

    gridLayout.children: [
        // row 1
        ILToggleLedButton {
            text: qsTr("Bathroom")
            ledColor: "#ff8800"
            Layout.fillWidth: true
        },

        ILToggleLedButton {
            text: qsTr("Bedroom")
            Layout.fillWidth: true
        },

        ILToggleLedButton {
            text: "Living Room"
            ledColor: "#ff0088"
            Layout.fillWidth: true
        },

        // row 2
        ILToggleLedButton {
            text: qsTr("Bathroom")
            ledColor: "#ff8800"
            Layout.fillWidth: true
            checked: true
        },

        ILToggleLedButton {
            text: qsTr("Bedroom")
            Layout.fillWidth: true
            checked: true
        },

        ILToggleLedButton {
            text: "Living Room"
            ledColor: "#ff0088"
            Layout.fillWidth: true
            checked: true
        },

        // row 3
        ILToggleLedButton {
            text: qsTr("Bathroom")
            ledColor: "#ff8800"
            Layout.fillWidth: true
            enabled: false
        },

        ILToggleLedButton {
            text: qsTr("Bedroom")
            Layout.fillWidth: true
            enabled: false
        },

        ILToggleLedButton {
            text: "Living Room"
            ledColor: "#ff0088"
            Layout.fillWidth: true
            enabled: false
        },

        // row 4
        ILToggleLedButton {
            text: qsTr("Bathroom")
            ledColor: "#ff8800"
            Layout.fillWidth: true
            enabled: false
            checked: true
        },

        ILToggleLedButton {
            text: qsTr("Bedroom")
            Layout.fillWidth: true
            enabled: false
            checked: true
        },

        ILToggleLedButton {
            text: "Living Room"
            ledColor: "#ff0088"
            Layout.fillWidth: true
            enabled: false
            checked: true
        }

        // row 5

    ]

}
