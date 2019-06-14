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
    property int lightMargin: 20
    property int controllerLightLabelMinimumWidth: 75

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

            ILControllerLightSectionLabel {
                text: "PWM Lights"
                horizontalAlignment: Text.AlignLeft
                Layout.fillWidth: true
                leftPadding: root.subtitleMargin
                visible: root.controller !== null && root.controller.pwmLights.count > 0
            }

            Repeater {
                model: root.controller !== null ? root.controller.pwmLights : undefined

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
                        Layout.leftMargin: root.lightMargin
                        text: "<b>Light %1<b>".arg(name)
                    }

                    ILControllerLight {
                        Layout.fillWidth: true
                        Layout.leftMargin: root.lightMargin
                        labelMinimumWidth: root.controllerLightLabelMinimumWidth
                        property int displayValue: 100 * (value - minValue) / (maxValue - minValue)
                        text: displayValue + "%"
                        light: model
                        value: model.value
                        onValueChanged: model.value = value
                    }
                }
            }

            ILControllerLightSectionLabel {
                text: "RGB Lights"
                horizontalAlignment: Text.AlignLeft
                Layout.fillWidth: true
                leftPadding: root.subtitleMargin
                visible: root.controller !== null && root.controller.rgbLights.count > 0
            }

            Repeater {
                model: root.controller !== null ? root.controller.rgbLights : null

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
                        Layout.leftMargin: root.lightMargin
                        text: "<b>Light %1<b>".arg(name)
                    }

                    ILControllerLight {
                        Layout.fillWidth: true
                        Layout.leftMargin: root.lightMargin
                        labelMinimumWidth: root.controllerLightLabelMinimumWidth
                        property int displayValue: 100 * (value - minValue) / (maxValue - minValue)
                        text: "%1% R".arg(displayValue)
                        value: model.redValue
                        light: model
                        onValueChanged: model.redValue = value
                    }

                    ILControllerLight {
                        Layout.fillWidth: true
                        Layout.leftMargin: root.lightMargin
                        labelMinimumWidth: root.controllerLightLabelMinimumWidth
                        property int displayValue: 100 * (value - minValue) / (maxValue - minValue)
                        text: "%1% G".arg(displayValue)
                        value: model.greenValue
                        light: model
                        onValueChanged: model.greenValue = value
                    }

                    ILControllerLight {
                        Layout.fillWidth: true
                        Layout.leftMargin: root.lightMargin
                        labelMinimumWidth: root.controllerLightLabelMinimumWidth
                        property int displayValue: 100 * (value - minValue) / (maxValue - minValue)
                        text: "%1% B".arg(displayValue)
                        value: model.blueValue
                        light: model
                        onValueChanged: model.blueValue = value
                    }
                }
            }

            ILControllerLightSectionLabel {
                text: "Analogic Lights"
                horizontalAlignment: Text.AlignLeft
                Layout.fillWidth: true
                leftPadding: root.subtitleMargin
                visible: root.controller !== null && root.controller.analogicLights.count > 0
            }

            Repeater {
                model: root.controller !== null ? root.controller.analogicLights : null

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
                        Layout.leftMargin: root.lightMargin
                        text: "<b>Light %1<b>".arg(name)
                    }

                    ILControllerLight {
                        Layout.fillWidth: true
                        Layout.leftMargin: root.lightMargin
                        labelMinimumWidth: root.controllerLightLabelMinimumWidth
                        property double displayValue: 10.0 * (value - minValue) / (maxValue - minValue)
                        text: displayValue.toFixed(2) + "V"
                        value: model.value
                        light: model
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
