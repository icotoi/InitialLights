import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

RowLayout {
    property var channel: undefined
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
        from: channel !== undefined ? channel.minValue: 0
        to: channel !== undefined ? channel.maxValue : 100
        stepSize: channel !== undefined ? channel.valueIncrement : 1
    }
}
