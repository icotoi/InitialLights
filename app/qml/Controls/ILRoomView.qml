import QtQuick 2.12
import QtQuick.Controls 2.12

import InitialLights 1.0

Item {
    id: control

    width: 300
    height: 300

    property alias lights: lightsRepeater.model
    property alias image: image.source
    property int currentIndex: -1

    function checkOnlyCurrentLight() {
        for (var index = 0; index < lightsRepeater.count; ++index) {
            var item = lightsRepeater.itemAt(index)
            if (index !== currentIndex)
                item.checked = false
        }
    }

    Image {
        id: image
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            control.currentIndex = -1
            checkOnlyCurrentLight()
        }
    }

    Repeater {
        id: lightsRepeater

        delegate: ILRoomLight {
            x: model.sideX
            y: model.sideY
            color: model.color
            onXChanged: model.sideX = x
            onYChanged: model.sideY = y
            lightIntensity: (model.lightType === Light.RGB)
            ? ((model.redValue + model.greenValue + model.blueValue) / 3 - model.minValue) / (model.maxValue - model.minValue)
            : (model.value - model.minValue) / (model.maxValue - model.minValue)
            dragTarget: control
            onToggled: {
                control.currentIndex = checked ? index : -1
                checkOnlyCurrentLight()
            }
            checked: control.currentIndex === index
        }
    }
}

