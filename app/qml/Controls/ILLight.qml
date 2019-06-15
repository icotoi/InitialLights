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
    property bool isControllerVisible: false
    property string label: qsTr("%1%2 Light")
    .arg(isControllerVisible
    ? ((model.controller.name !== ""
    ? model.controller.name : model.controller.address) + ": ")
    : "")
    .arg(model.lightTypeName)

    height: rowLayout.height

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
                text: model.name
                onTextChanged: model.name = text
                placeholderText: qsTr("Light Name")
                Layout.fillWidth: true
                Layout.leftMargin: root.margins
                Layout.rightMargin: root.margins
            }

            Rectangle {
                visible: model.lightType === Light.RGB
                Layout.leftMargin: root.margins
                Layout.fillWidth: true
//                width: root.colorSwatchSize
                height: root.colorSwatchSize
                radius: root.colorSwatchRadius
                color:  "#%1%2%3"
                .arg(model.redValue.toString(16).padStart(2, '0'))
                .arg(model.greenValue.toString(16).padStart(2, '0'))
                .arg(model.blueValue.toString(16).padStart(2, '0'))
            }

            ILLabeledSlider {
                visible: model.lightType === Light.Analogic
                Layout.fillWidth: true
                Layout.leftMargin: root.margins
                Layout.rightMargin: root.margins
                labelMinimumWidth: root.valueLabelMinimumWidth
                property double displayValue: 10.0 * (value - minValue) / (maxValue - minValue)
                text: displayValue.toFixed(2) + "V"
                value: model.value
                light: model
                onValueChanged: model.value = value
            }

            ILLabeledSlider {
                visible: model.lightType === Light.PWM// || model.lightType === Light.RGB
                Layout.fillWidth: true
                Layout.leftMargin: root.margins
                Layout.rightMargin: root.margins
                labelMinimumWidth: root.valueLabelMinimumWidth
                property int displayValue: 100 * (value - minValue) / (maxValue - minValue)
                text: displayValue + "%"
                light: model
                value: model.value
                onValueChanged: model.value = value
            }

            ILLabeledSlider {
                visible: model.lightType === Light.RGB
                Layout.fillWidth: true
                Layout.leftMargin: root.margins
                Layout.rightMargin: root.margins
                labelMinimumWidth: root.valueLabelMinimumWidth
                property int displayValue: 100 * (value - minValue) / (maxValue - minValue)
                text: "%1% R".arg(displayValue)
                value: model.redValue
                light: model
                onValueChanged: model.redValue = value
            }

            ILLabeledSlider {
                visible: model.lightType === Light.RGB
                Layout.fillWidth: true
                Layout.leftMargin: root.margins
                Layout.rightMargin: root.margins
                labelMinimumWidth: root.valueLabelMinimumWidth
                property int displayValue: 100 * (value - minValue) / (maxValue - minValue)
                text: "%1% G".arg(displayValue)
                value: model.greenValue
                light: model
                onValueChanged: model.greenValue = value
            }

            ILLabeledSlider {
                visible: model.lightType === Light.RGB
                Layout.fillWidth: true
                Layout.leftMargin: root.margins
                Layout.rightMargin: root.margins
                labelMinimumWidth: root.valueLabelMinimumWidth
                property int displayValue: 100 * (value - minValue) / (maxValue - minValue)
                text: "%1% B".arg(displayValue)
                value: model.blueValue
                light: model
                onValueChanged: model.blueValue = value
            }
        }
        Switch {}
    }
}
