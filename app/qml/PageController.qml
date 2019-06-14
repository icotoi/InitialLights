import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.12

import "Images"
import "Controls"
import "Constants"

import InitialLights 1.0

Item {
    id: root

    property var controller: null
    property int smallMargins: 8
    property int valueLabelMinimumWidth: 50

    property string title: controller !== null
                           ? (controller.name !== ""
                              ? controller.name
                              : controller.address)
                           : "(controller)"
    property string message: controller !== null
                             ? controller.message
                             : ""

    ListModel {
        id: designModel
        ListElement {
            name: "foo"
            lightTypeName: "Analogic"
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
            lightTypeName: "PWM"
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
            width: parent.width

            Label {
                text: qsTr("%1 Light").arg(model.lightTypeName)
                font.italic: true
                font.pointSize: 8
                Layout.fillWidth: true
                Layout.topMargin: root.smallMargins
                Layout.leftMargin: root.smallMargins
                Layout.rightMargin: root.smallMargins
                color: Material.accent
            }

            TextField {
                text: model.name
                onTextChanged: model.name = text
                placeholderText: qsTr("Light Name")
                Layout.fillWidth: true
                Layout.leftMargin: root.smallMargins
                Layout.rightMargin: root.smallMargins
            }

            ILControllerLight {
                visible: model.lightType === Light.Analogic
                Layout.fillWidth: true
                Layout.leftMargin: root.smallMargins
                Layout.rightMargin: root.smallMargins
                labelMinimumWidth: root.valueLabelMinimumWidth
                property double displayValue: 10.0 * (value - minValue) / (maxValue - minValue)
                text: displayValue.toFixed(2) + "V"
                value: model.value
                light: model
                onValueChanged: model.value = value
            }

            ILControllerLight {
                visible: model.lightType === Light.PWM
                Layout.fillWidth: true
                Layout.leftMargin: root.smallMargins
                Layout.rightMargin: root.smallMargins
                labelMinimumWidth: root.valueLabelMinimumWidth
                property int displayValue: 100 * (value - minValue) / (maxValue - minValue)
                text: displayValue + "%"
                light: model
                value: model.value
                onValueChanged: model.value = value
            }

            ILControllerLight {
                visible: model.lightType === Light.RGB
                Layout.fillWidth: true
                Layout.leftMargin: root.smallMargins
                Layout.rightMargin: root.smallMargins
                labelMinimumWidth: root.valueLabelMinimumWidth
                property int displayValue: 100 * (value - minValue) / (maxValue - minValue)
                text: "%1% R".arg(displayValue)
                value: model.redValue
                light: model
                onValueChanged: model.redValue = value
            }

            ILControllerLight {
                visible: model.lightType === Light.RGB
                Layout.fillWidth: true
                Layout.leftMargin: root.smallMargins
                Layout.rightMargin: root.smallMargins
                labelMinimumWidth: root.valueLabelMinimumWidth
                property int displayValue: 100 * (value - minValue) / (maxValue - minValue)
                text: "%1% G".arg(displayValue)
                value: model.greenValue
                light: model
                onValueChanged: model.greenValue = value
            }

            ILControllerLight {
                visible: model.lightType === Light.RGB
                Layout.fillWidth: true
                Layout.leftMargin: root.smallMargins
                Layout.rightMargin: root.smallMargins
                labelMinimumWidth: root.valueLabelMinimumWidth
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
