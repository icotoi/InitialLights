import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

RowLayout {
    property var light: undefined
    property alias text: label.text
    property alias value: slider.value
    property int labelMinimumWidth: 50

    Label {
        id: label
        Layout.minimumWidth: labelMinimumWidth
        horizontalAlignment: Text.AlignRight
    }

    Slider {
        id: slider
        Layout.fillWidth: true
        from: light !== undefined ? light.minValue: 0
        to: light !== undefined ? light.maxValue : 100
        stepSize: light !== undefined ? light.valueIncrement : 1
    }
}
