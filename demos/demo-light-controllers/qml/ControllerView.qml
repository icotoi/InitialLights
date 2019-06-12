import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: control

    property var controller: undefined
    property int subtitleMargin: 10
    property int channelMargin: 20
    property int controllerChannelLabelMinimumWidth: 75

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
            visible: controller !== null && controller.pwmChannels.count > 0
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
                    text: "<b>Channel %1<b>".arg(name)
                }

                ControllerChannel {
                    Layout.fillWidth: true
                    Layout.leftMargin: control.channelMargin
                    labelMinimumWidth: control.controllerChannelLabelMinimumWidth
                    property int displayValue: 100 * (value - minValue) / (maxValue - minValue)
                    text: displayValue + "%"
                    value: model.value
                    minValue: model.minValue
                    maxValue: model.maxValue
                    valueIncrement: model.valueIncrement
                    onValueChanged: model.value = value
                }
            }
        }

        SectionLabel {
            id: rgbChannelsLabel
            text: "RGB Channels"
            horizontalAlignment: Text.AlignLeft
            Layout.fillWidth: true
            leftPadding: control.subtitleMargin
            visible: controller !== null && controller.rgbChannels.count > 0
        }

        Repeater {
            id: rgbChannelsRepeater

            model: QtObject {
                property string version: "v1"
                property string name: "1"
                property int redValue: 5
                property int greenValue: 5
                property int blueValue: 5
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
                    text: "<b>Channel %1<b>".arg(name)
                }

                ControllerChannel {
                    Layout.fillWidth: true
                    Layout.leftMargin: control.channelMargin
                    labelMinimumWidth: control.controllerChannelLabelMinimumWidth
                    property int displayValue: 100 * (value - minValue) / (maxValue - minValue)
                    text: "%1% R".arg(displayValue)
                    value: model.redValue
                    minValue: model.minValue
                    maxValue: model.maxValue
                    valueIncrement: model.valueIncrement
                    onValueChanged: model.redValue = value
                }

                ControllerChannel {
                    Layout.fillWidth: true
                    Layout.leftMargin: control.channelMargin
                    labelMinimumWidth: control.controllerChannelLabelMinimumWidth
                    property int displayValue: 100 * (value - minValue) / (maxValue - minValue)
                    text: "%1% G".arg(displayValue)
                    value: model.greenValue
                    minValue: model.minValue
                    maxValue: model.maxValue
                    valueIncrement: model.valueIncrement
                    onValueChanged: model.greenValue = value
                }

                ControllerChannel {
                    Layout.fillWidth: true
                    Layout.leftMargin: control.channelMargin
                    labelMinimumWidth: control.controllerChannelLabelMinimumWidth
                    property int displayValue: 100 * (value - minValue) / (maxValue - minValue)
                    text: "%1% B".arg(displayValue)
                    value: model.blueValue
                    minValue: model.minValue
                    maxValue: model.maxValue
                    valueIncrement: model.valueIncrement
                    onValueChanged: model.blueValue = value
                }
            }
        }

        SectionLabel {
            id: voltageChannelsLabel
            text: "Voltage Channels"
            horizontalAlignment: Text.AlignLeft
            Layout.fillWidth: true
            leftPadding: control.subtitleMargin
            visible: controller !== null && controller.voltageChannels.count > 0
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
                    text: "<b>Channel %1<b>".arg(name)
                }

                ControllerChannel {
                    Layout.fillWidth: true
                    Layout.leftMargin: control.channelMargin
                    labelMinimumWidth: control.controllerChannelLabelMinimumWidth
                    property double displayValue: 10.0 * (value - minValue) / (maxValue - minValue)
                    text: displayValue.toFixed(2) + "V"
                    value: model.value
                    minValue: model.minValue
                    maxValue: model.maxValue
                    valueIncrement: model.valueIncrement
                    onValueChanged: model.value = value
                }
            }
        }
    }

    BusyIndicator {
        id: busyIndicator
        anchors.centerIn: parent
        visible: controller !== null && controller.isBusy
    }

    onControllerChanged: {
        if (controller != undefined) {
            controller.connectToController()
            titleLabel.text = controller.name === "" ? controller.address : controller.name
            pwmChannelsRepeater.model = controller.pwmChannels
            voltageChannelsRepeater.model = controller.voltageChannels
            rgbChannelsRepeater.model = controller.rgbChannels
        }
    }
}
