import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "Images"
import "Controls"
import "Constants"

Item {
    id: root

    property var controller: null
    property int subtitleMargin: 10
    property int channelMargin: 20
    property int controllerChannelLabelMinimumWidth: 75

    property string title: controller !== null
                           ? (controller.name !== ""
                              ? controller.name
                              : controller.address)
                           : "(controller)"
    property string message: controller !== null
                             ? controller.message
                             : ""

    onControllerChanged: {
        if (controller !== null) {
            controller.connectToController()
        }
    }

    Flickable {
        anchors.fill: parent
        contentHeight: contentColumn.height

        ColumnLayout {
            id: contentColumn
            width: parent.width

            ILControllerChannelSectionLabel {
                text: "PWM Channels"
                horizontalAlignment: Text.AlignLeft
                Layout.fillWidth: true
                leftPadding: root.subtitleMargin
                visible: root.controller !== null && root.controller.pwmChannels.count > 0
            }

            Repeater {
                model: root.controller !== null ? root.controller.pwmChannels : undefined

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
                        Layout.leftMargin: root.channelMargin
                        text: "<b>Channel %1<b>".arg(name)
                    }

                    ILControllerChannel {
                        Layout.fillWidth: true
                        Layout.leftMargin: root.channelMargin
                        labelMinimumWidth: root.controllerChannelLabelMinimumWidth
                        property int displayValue: 100 * (value - minValue) / (maxValue - minValue)
                        text: displayValue + "%"
                        channel: model
                        value: model.value
                        onValueChanged: model.value = value
                    }
                }
            }

            ILControllerChannelSectionLabel {
                text: "RGB Channels"
                horizontalAlignment: Text.AlignLeft
                Layout.fillWidth: true
                leftPadding: root.subtitleMargin
                visible: root.controller !== null && root.controller.rgbChannels.count > 0
            }

            Repeater {
                model: root.controller !== null ? root.controller.rgbChannels : null

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
                        Layout.leftMargin: root.channelMargin
                        text: "<b>Channel %1<b>".arg(name)
                    }

                    ILControllerChannel {
                        Layout.fillWidth: true
                        Layout.leftMargin: root.channelMargin
                        labelMinimumWidth: root.controllerChannelLabelMinimumWidth
                        property int displayValue: 100 * (value - minValue) / (maxValue - minValue)
                        text: "%1% R".arg(displayValue)
                        value: model.redValue
                        channel: model
                        onValueChanged: model.redValue = value
                    }

                    ILControllerChannel {
                        Layout.fillWidth: true
                        Layout.leftMargin: root.channelMargin
                        labelMinimumWidth: root.controllerChannelLabelMinimumWidth
                        property int displayValue: 100 * (value - minValue) / (maxValue - minValue)
                        text: "%1% G".arg(displayValue)
                        value: model.greenValue
                        channel: model
                        onValueChanged: model.greenValue = value
                    }

                    ILControllerChannel {
                        Layout.fillWidth: true
                        Layout.leftMargin: root.channelMargin
                        labelMinimumWidth: root.controllerChannelLabelMinimumWidth
                        property int displayValue: 100 * (value - minValue) / (maxValue - minValue)
                        text: "%1% B".arg(displayValue)
                        value: model.blueValue
                        channel: model
                        onValueChanged: model.blueValue = value
                    }
                }
            }

            ILControllerChannelSectionLabel {
                text: "Analogic Channels"
                horizontalAlignment: Text.AlignLeft
                Layout.fillWidth: true
                leftPadding: root.subtitleMargin
                visible: root.controller !== null && root.controller.analogicChannels.count > 0
            }

            Repeater {
                model: root.controller !== null ? root.controller.analogicChannels : null

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
                        Layout.leftMargin: root.channelMargin
                        text: "<b>Channel %1<b>".arg(name)
                    }

                    ILControllerChannel {
                        Layout.fillWidth: true
                        Layout.leftMargin: root.channelMargin
                        labelMinimumWidth: root.controllerChannelLabelMinimumWidth
                        property double displayValue: 10.0 * (value - minValue) / (maxValue - minValue)
                        text: displayValue.toFixed(2) + "V"
                        value: model.value
                        channel: model
                        onValueChanged: model.value = value
                    }
                }
            }
        }
    }

    BusyIndicator {
        id: busyIndicator
        anchors.centerIn: parent
        visible: root.controller !== null && root.controller.isBusy
    }

    Label {
        visible: root.message !== ""
        text: root.message
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        horizontalAlignment: Text.AlignHCenter

        background: Rectangle {
            color: "black"
            opacity: 0.2
        }
    }
}
