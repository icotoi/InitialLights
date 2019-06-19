import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12

import "../Constants"

Item {
    id: control
    width: 50
    height: 50

    property var dragTarget: null

    property int size: Math.min(width, height)
    property color color: "white"
    property bool isOn: false

    property alias checked: button.checked

    property real onOpacity: 0.75
    property real offOpacity: 0.25

    property color buttonBorderColor: ILStyle.circularToggleLedButton.borderColor
    property int buttonBorderWidth: 2

    property real lightIntensity: 0.3
    property int lightIndicatorWidth: 3

    signal toggled()

    AbstractButton {
        id: button
        checked: false
        anchors.fill: parent
        checkable: true

        background: Item {
            Rectangle {
                width: control.size
                height: width
                radius: width / 2
                color: control.color
                opacity: lightIntensity // control.isOn ? control.onOpacity : control.offOpacity
            }

            Rectangle {
                width: control.size
                height: width
                radius: width / 2
                border.color: control.checked ? Material.accent : control.buttonBorderColor
                border.width: control.buttonBorderWidth
                color: "transparent"
            }

            Rectangle {
                id: intensityBackground
                x: (button.width + control.size + control.lightIndicatorWidth) / 2
                height: control.size
                width: control.lightIndicatorWidth
                radius: width / 2
                color: "black"
                opacity: 0.5
            }

            Rectangle {
                id: itensity
                x: intensityBackground.x
                y: control.size - height
                height: control.size * control.lightIntensity
                width: control.lightIndicatorWidth
                radius: width / 2
                color: control.buttonBorderColor
            }
        }

        MouseArea {
            id: mouseArea

            anchors.fill: parent

            property bool held: false

            drag.target: held ? control : undefined
            drag.minimumX: 0
            drag.minimumY: 0
            onPressed: held = true
            onPositionChanged: {
                if (!button.checked) {
                    button.checked = true
                    control.toggled()
                }
            }
            onReleased: held = false
            onClicked: {
                button.toggle()
                control.toggled()
            }
        }
    }

    onDragTargetChanged: {
        if (dragTarget) {
            mouseArea.drag.maximumX = dragTarget.width - control.width
            mouseArea.drag.maximumY = dragTarget.height - control.height
        }
    }
}
