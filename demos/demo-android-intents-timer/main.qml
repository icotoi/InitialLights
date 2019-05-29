import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Android Intents: Timer")

    ColumnLayout {
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width

        Label {
            text: qsTr("Timer name:")
        }

        TextField {
            id: textField
            text: "dummy"
            Layout.fillWidth: true
        }

        RowLayout {
            id: rowLayout
            width: 100
            height: 100

            Label {
                text: qsTr("Duration:")
            }

            Label {
                id: sliderValueLabel
                text: slider.value
            }
        }

        Slider {
            id: slider
            snapMode: Slider.SnapAlways
            stepSize: 0.1
            from: 1.0
            to: 10.0
            Layout.fillWidth: true
        }

        Switch {
            id: uiSwitch
            text: qsTr("Show Timer UI")
            checked: true
        }

        Button {
            text: "Set timer"
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            onClicked: {
                var title = textField.text != "" ? textField.text : "dummy"
                var duration = slider.value
                var showUI = uiSwitch.checked
                timer.createTimer(title, duration, showUI)
            }
        }
    }

}
