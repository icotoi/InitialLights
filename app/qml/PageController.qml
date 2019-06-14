import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "Images"
import "Controls"
import "Constants"

import InitialLights 1.0

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

    ListModel {
        id: designModel
        ListElement {
            name: "foo"
            minValue: 0
            maxValue: 255
            valueIncrement: 1
            value: 4
            redValue: 0
            greenValue: 128
            blueValue: 255
        }
        ListElement {
            name: "bar"
            minValue: 0
            maxValue: 255
            valueIncrement: 1
            value: 10
            redValue: 128
            greenValue: 255
            blueValue: 0
        }
    }

    ListView {
        id: listView
        anchors.fill: parent

        model: root.controller !== null ? root.controller.lights : designModel

        delegate: ColumnLayout {

            Rectangle {
                Layout.fillWidth: true
                height: 1
                color: "gray"
                visible: index > 0
            }

            TextField {
                Layout.fillWidth: true
                Layout.leftMargin: root.lightMargin
                text: model.name
                onTextChanged: model.name = text
            }

            ILControllerLight {
                visible: model.lightType === Light.Analogic
                Layout.fillWidth: true
                Layout.leftMargin: root.lightMargin
                labelMinimumWidth: root.controllerLightLabelMinimumWidth
                property double displayValue: 10.0 * (value - minValue) / (maxValue - minValue)
                text: displayValue.toFixed(2) + "V"
                value: model.value
                light: model
                onValueChanged: model.value = value
            }

            ILControllerLight {
                visible: model.lightType === Light.PWM
                Layout.fillWidth: true
                Layout.leftMargin: root.lightMargin
                labelMinimumWidth: root.controllerLightLabelMinimumWidth
                property int displayValue: 100 * (value - minValue) / (maxValue - minValue)
                text: displayValue + "%"
                light: model
                value: model.value
                onValueChanged: model.value = value
            }

            ILControllerLight {
                visible: model.lightType === Light.RGB
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
                visible: model.lightType === Light.RGB
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
                visible: model.lightType === Light.RGB
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
