import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: control

    property var controller: undefined
    property int subtitleMargin: 10
    property int channelMargin: 20

    SectionLabel {
        id: titleLabel
        text: "{xxx-xxx-xxx}"
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
    }

    ColumnLayout {
        anchors.top: titleLabel.bottom
        anchors.right: parent.right
        anchors.left: parent.left

        SectionLabel {
            id: pwmChannelsLabel
            text: "PWM Channels"
            horizontalAlignment: Text.AlignLeft
            Layout.fillWidth: true
            leftPadding: control.subtitleMargin
        }

        Repeater {
            id: pwmChannelsRepeater

            model: QtObject {
                property string version: "pwm.v1"
                property string name: "1"
                property int value: 20
            }

            delegate: ColumnLayout {
                Layout.fillWidth: true

                Rectangle {
                    Layout.fillWidth: true
                    height: 1
                    color: "gray"
                    visible: index > 0
                }

                Label {
                    Layout.fillWidth: true
                    Layout.leftMargin: control.channelMargin
                    property int displayValue: 100 * (value - minValue) / (maxValue - minValue)
                    text: "<b>Channel %1<b>: %2".arg(name).arg(displayValue)
                }

                Slider {
                    Layout.fillWidth: true
                    Layout.leftMargin: control.channelMargin
                    from: model.minValue
                    to: model.maxValue
                    stepSize: model.valueIncrement
                    value: model.value
                    onValueChanged: model.value = value
                }
            }
        }

        SectionLabel {
            id: voltageChannelsLabel
            text: "Voltage Channels"
            horizontalAlignment: Text.AlignLeft
            Layout.fillWidth: true
            leftPadding: control.subtitleMargin
        }

        Repeater {
            id: voltageChannelsRepeater

            model: QtObject {
                property string version: "voltage.v1"
                property string name: "1"
                property int value: 5
            }

            delegate: ColumnLayout {
                Layout.fillWidth: true

                Rectangle {
                    Layout.fillWidth: true
                    height: 1
                    color: "gray"
                    visible: index > 0
                }

                Label {
                    Layout.fillWidth: true
                    Layout.leftMargin: control.channelMargin
                    property double displayValue: 10.0 * (value - minValue) / (maxValue - minValue)
                    text: "<b>Channel %1<b>: %2V".arg(name).arg(displayValue)
                }

                Slider {
                    Layout.fillWidth: true
                    Layout.leftMargin: control.channelMargin
                    from: model.minValue
                    to: model.maxValue
                    stepSize: model.valueIncrement
                    value: model.value
                    onValueChanged: model.value = value
                }
            }
        }
    }

    onControllerChanged: {
        if (controller != undefined) {
            controller.connectToController()
            titleLabel.text = controller.name === "" ? controller.address : controller.name
            pwmChannelsRepeater.model = controller.pwmChannels
            voltageChannelsRepeater.model = controller.voltageChannels
        }
    }
}
