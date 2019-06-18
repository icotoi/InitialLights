import QtQuick 2.12
import QtQuick.Controls 2.12

import InitialLights 1.0

Item {
    id: control

    width: 300
    height: 300

    property alias lights: lightsRepeater.model
    property alias image: image.source
    property var currentLight: null

//    function removeCurrentLight() {
//        if (currentLight) {
//            var index = _.lights.indexOf(currentLight)
//            if (index < 0) {
//                console.warn("currentLight not found in the list of lights!")
//                return
//            }

//            _.lights.splice(index, 1)
//            currentLight.destroy()
//            currentLight = null
//            _.configureCurrentLight()
//        }
//    }

//    QtObject {
//        id: _
//        property var lights: []

//        function configureCurrentLight() {
//            lights.forEach(function(light){
//                if (light !== currentLight) {
//                    light.checked = false
//                }
//            })
//        }
//    }

    Image {
        id: image
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            currentLight = null
//            _.configureCurrentLight()
        }
    }

//    Component.onCompleted: {
//        var lights = []
//        for(var i = 0; i < children.length; ++i) {
//            var child = children[i]
//            if (child instanceof ILRoomLight) {
//                lights.push(child)
//            }
//        }

//        lights.forEach(function(light) {
//            add(light)
//        })
//    }

    Repeater {
        id: lightsRepeater

        delegate: ILRoomLight {
            x: model.sideX
            y: model.sideY
            onXChanged: model.sideX = x
            onYChanged: model.sideY = y
            lightIntensity: (model.lightType === Light.RGB)
            ? ((model.redValue + model.greenValue + model.blueValue) / 3 - model.minValue) / (model.maxValue - model.minValue)
            : (model.value - model.minValue) / (model.maxValue - model.minValue)
            dragTarget: control
            onToggled: {
                //            currentLight = light.checked ? light : null
                //            _.configureCurrentLight()
            }
        }
    }
}

