import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

RowLayout {
    property alias value: slider.value
    property alias minValue: slider.from
    property alias maxValue: slider.to
    property alias valueIncrement: slider.stepSize
    property alias text: label.text
    property int labelMinimumWidth: 50

    Label {
        id: label
        Layout.minimumWidth: labelMinimumWidth
        horizontalAlignment: Text.AlignRight
    }

    Slider {
        id: slider
        Layout.fillWidth: true
    }
}
