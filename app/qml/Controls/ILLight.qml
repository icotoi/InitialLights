import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.12

import "../Constants"

import InitialLights 1.0

Item {
    id: root

    property int margins: 8
    property int valueLabelMinimumWidth: 50
    property int colorSwatchSize: 40
    property int colorSwatchRadius: 5

    property bool isControllerNameVisible: true
    property bool rgbSlidersVisible: true

    property string controllerName: "Controller"

    property var light: null

    property string label: qsTr("%1%2 Light").arg(isControllerNameVisible ? (controllerName + ": ") : "").arg(light !== null ? light.lightTypeName : "")

    height: rowLayout.height

    signal colorSwatchClicked(var color)

    RowLayout {
        id: rowLayout
        width: parent.width

        ColumnLayout {
            id: columnLayout
            width: parent.width

            Label {
                text: root.label
                font.italic: true
                font.pointSize: 8
                Layout.fillWidth: true
                Layout.topMargin: root.margins
                Layout.leftMargin: root.margins
                Layout.rightMargin: root.margins
                color: Material.accent
            }

            TextField {
                id: nameTextField
                placeholderText: qsTr("Light Name")
                Layout.fillWidth: true
                Layout.leftMargin: root.margins
                Layout.rightMargin: root.margins
                text: root.light !== null ? root.light.name : "Light"
                onTextChanged: if (root.light !== null) { root.light.name = nameTextField.text }
            }

            Rectangle {
                visible: root.light !== null && root.light.lightType === Light.RGB
                Layout.leftMargin: root.margins
                Layout.rightMargin: root.margins
                Layout.fillWidth: true
//                width: root.colorSwatchSize
                height: root.colorSwatchSize
                radius: root.colorSwatchRadius
                color:  root.light !== null ? root.light.color : "white"

                MouseArea {
                    anchors.fill: parent
                    onClicked: root.colorSwatchClicked(parent.color)
                }
            }

            ILLabeledSlider {
                id: analogicSlider
                visible: root.light !== null && root.light.lightType === Light.Analogic
                Layout.fillWidth: true
                Layout.leftMargin: root.margins
                Layout.rightMargin: root.margins
                labelMinimumWidth: root.valueLabelMinimumWidth
                property double displayValue: root.light !== null
                                              ? 10.0 * (value - minValue) / (maxValue - minValue)
                                              : 0
                text: displayValue.toFixed(2) + "V"

                minValue: root.light !== null ? root.light.minValue : 0
                maxValue: root.light !== null ? root.light.maxValue : 100
                valueIncrement: root.light !== null ? root.light.valueIncrement : 1
                value: root.light !== null ? root.light.value : 0
                onValueChanged: if (root.light !== null) root.light.value = analogicSlider.value
            }

            ILLabeledSlider {
                id: pwmSlider
                visible: root.light !== null && root.light.lightType === Light.PWM
                Layout.fillWidth: true
                Layout.leftMargin: root.margins
                Layout.rightMargin: root.margins
                labelMinimumWidth: root.valueLabelMinimumWidth
                property int displayValue: root.light !== null
                                           ? 100 * (value - minValue) / (maxValue - minValue)
                                           : 0
                text: displayValue + "%"

                minValue: root.light !== null ? root.light.minValue : 0
                maxValue: root.light !== null ? root.light.maxValue : 100
                valueIncrement: root.light !== null ? root.light.valueIncrement : 1
                value: root.light !== null ? root.light.value : 0
                onValueChanged: if (root.light !== null) root.light.value = pwmSlider.value
            }

            ILLabeledSlider {
                id: redSlider
                visible: root.light !== null && root.rgbSlidersVisible && root.light.lightType === Light.RGB
                Layout.fillWidth: true
                Layout.leftMargin: root.margins
                Layout.rightMargin: root.margins
                labelMinimumWidth: root.valueLabelMinimumWidth
                property int displayValue: root.light !== null
                                           ? 100 * (value - minValue) / (maxValue - minValue)
                                           : 0
                text: "%1% R".arg(displayValue)

                minValue: root.light !== null ? root.light.minValue : 0
                maxValue: root.light !== null ? root.light.maxValue : 100
                valueIncrement: root.light !== null ? root.light.valueIncrement : 1
                value: root.light !== null ? root.light.redValue : 0
                onValueChanged: if (root.light !== null) root.light.redValue = redSlider.value
            }

            ILLabeledSlider {
                id: greenSlider
                visible: root.light !== null && root.rgbSlidersVisible && root.light.lightType === Light.RGB
                Layout.fillWidth: true
                Layout.leftMargin: root.margins
                Layout.rightMargin: root.margins
                labelMinimumWidth: root.valueLabelMinimumWidth
                property int displayValue: root.light !== undefined
                                           ? 100 * (value - minValue) / (maxValue - minValue)
                                           : 0
                text: "%1% G".arg(displayValue)

                minValue: root.light !== null ? root.light.minValue : 0
                maxValue: root.light !== null ? root.light.maxValue : 100
                valueIncrement: root.light !== null ? root.light.valueIncrement : 1
                value: root.light !== null ? root.light.greenValue : 0
                onValueChanged: if (root.light !== null) root.light.greenValue = greenSlider.value
            }

            ILLabeledSlider {
                id: blueSlider
                visible: root.light !== null && root.rgbSlidersVisible && root.light.lightType === Light.RGB
                Layout.fillWidth: true
                Layout.leftMargin: root.margins
                Layout.rightMargin: root.margins
                labelMinimumWidth: root.valueLabelMinimumWidth
                property int displayValue: root.light !== undefined
                                           ? 100 * (value - minValue) / (maxValue - minValue)
                                           : 0
                text: "%1% B".arg(displayValue)

                minValue: root.light !== null ? root.light.minValue : 0
                maxValue: root.light !== null ? root.light.maxValue : 100
                valueIncrement: root.light !== null ? root.light.valueIncrement : 1
                value: root.light !== null ? root.light.blueValue : 0
                onValueChanged: if (root.light !== null) root.light.blueValue = blueSlider.value
            }
        }

        ColumnLayout {
            ToolButton {
                icon.source: "../Images/material.io-baseline-wb_incandescent-24px.svg"
                onClicked: if (light !== null) light.blink(0)
            }

            ToolButton {
                visible: root.light !== null && root.light.lightType === Light.RGB
                icon.source: "../Images/material.io-baseline-wb_incandescent-24px.svg"
                onClicked: if (light !== null) light.blink(1)
            }

            ToolButton {
                visible: root.light !== null && root.light.lightType === Light.RGB
                icon.source: "../Images/material.io-baseline-wb_incandescent-24px.svg"
                onClicked: if (light !== null) light.blink(2)
            }

            Switch {
                visible: true
            }
        }
    }
}
