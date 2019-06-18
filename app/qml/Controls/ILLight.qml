import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.12

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

    property var light

    property var lightName: light !== undefined ? light.name : ""
    property int lightMinValue: light !== undefined ? light.minValue : 0
    property int lightMaxValue: light !== undefined ? light.maxValue : 255
    property int lightValueIncrement: light !== undefined ? light.valueIncrement : 1
    property int lightValue: light !== undefined ? light.value : 0
    property int lightRedValue: light !== undefined ? light.redValue : 0
    property int lightGreenValue: light !== undefined ? light.greenValue : 0
    property int lightBlueValue: light !== undefined ? light.blueValue : 0
    property var lightType: light !== undefined ? light.lightType : undefined
    property string lightTypeName: light !== undefined ? light.lightTypeName : ""

    property string label: qsTr("%1%2 Light").arg(isControllerNameVisible ? (controllerName + ": ") : "").arg(lightTypeName)

    height: rowLayout.height

    signal colorSwatchCliked(var color)

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
                text: root.lightName
                onTextChanged: if (root.light) { root.light.name = text }
                placeholderText: qsTr("Light Name")
                Layout.fillWidth: true
                Layout.leftMargin: root.margins
                Layout.rightMargin: root.margins
            }

            Rectangle {
                visible: root.lightType === Light.RGB
                Layout.leftMargin: root.margins
                Layout.fillWidth: true
//                width: root.colorSwatchSize
                height: root.colorSwatchSize
                radius: root.colorSwatchRadius
                color:  "#%1%2%3"
                .arg(root.lightRedValue.toString(16).padStart(2, '0'))
                .arg(root.lightGreenValue.toString(16).padStart(2, '0'))
                .arg(root.lightBlueValue.toString(16).padStart(2, '0'))

                MouseArea {
                    anchors.fill: parent
                    onClicked: root.colorSwatchClicked(parent.color)
                }
            }

            ILLabeledSlider {
                visible: root.lightType === Light.Analogic
                Layout.fillWidth: true
                Layout.leftMargin: root.margins
                Layout.rightMargin: root.margins
                labelMinimumWidth: root.valueLabelMinimumWidth
                property double displayValue: 10.0 * (value - root.lightMinValue) / (root.lightMaxValue - root.lightMinValue)
                text: displayValue.toFixed(2) + "V"
                value: root.lightValue
                light: root.light
                onValueChanged: if (root.light !== undefined) root.light.value = value
            }

            ILLabeledSlider {
                visible: root.lightType === Light.PWM
                Layout.fillWidth: true
                Layout.leftMargin: root.margins
                Layout.rightMargin: root.margins
                labelMinimumWidth: root.valueLabelMinimumWidth
                property int displayValue: 100 * (value - root.lightMinValue) / (root.lightMaxValue - root.lightMinValue)
                text: displayValue + "%"
                light: root.light
                value: root.lightValue
                onValueChanged: if (root.light !== undefined) root.light.value = value
            }

            ILLabeledSlider {
                visible: root.rgbSlidersVisible && root.lightType === Light.RGB
                Layout.fillWidth: true
                Layout.leftMargin: root.margins
                Layout.rightMargin: root.margins
                labelMinimumWidth: root.valueLabelMinimumWidth
                property int displayValue: 100 * (value - root.lightMinValue) / (root.lightMaxValue - root.lightMinValue)
                text: "%1% R".arg(displayValue)
                value: root.lightRedValue
                light: root.light
                onValueChanged: if (root.light !== undefined) root.light.redValue = value
            }

            ILLabeledSlider {
                visible: root.rgbSlidersVisible && root.lightType === Light.RGB
                Layout.fillWidth: true
                Layout.leftMargin: root.margins
                Layout.rightMargin: root.margins
                labelMinimumWidth: root.valueLabelMinimumWidth
                property int displayValue: 100 * (value - root.lightMinValue) / (root.lightMaxValue - root.lightMinValue)
                text: "%1% G".arg(displayValue)
                value: root.lightGreenValue
                light: root.light
                onValueChanged: if (root.light !== undefined) root.light.greenValue = value
            }

            ILLabeledSlider {
                visible: root.rgbSlidersVisible && root.lightType === Light.RGB
                Layout.fillWidth: true
                Layout.leftMargin: root.margins
                Layout.rightMargin: root.margins
                labelMinimumWidth: root.valueLabelMinimumWidth
                property int displayValue: 100 * (value - root.lightMinValue) / (root.lightMaxValue - root.lightMinValue)
                text: "%1% B".arg(displayValue)
                value: root.lightBlueValue
                light: root.light
                onValueChanged: if (root.light !== undefined) root.light.blueValue = value
            }
        }
        Switch {}
    }
}
