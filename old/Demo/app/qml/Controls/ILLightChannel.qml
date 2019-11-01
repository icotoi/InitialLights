import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

RowLayout {
    id: control

    property alias value: slider.value
    property alias minValue: slider.from
    property alias maxValue: slider.to
    property alias valueIncrement: slider.stepSize
    property alias text: label.text
    property int labelMinimumWidth: 50

    signal blink()

    Label {
        id: label
        Layout.minimumWidth: labelMinimumWidth
        horizontalAlignment: Text.AlignRight
    }

    Slider {
        id: slider
        Layout.fillWidth: true
    }

    ToolButton {
        icon.source: "../Images/material.io-baseline-wb_incandescent-24px--blink.svg"
        onClicked: control.blink()
        Rectangle {
            color: "transparent"
            anchors.centerIn: parent
            width: 36
            height: width
            radius: width / 2
            border.width: 1
            border.color: label.color
            opacity: 0.3
        }
    }
}
