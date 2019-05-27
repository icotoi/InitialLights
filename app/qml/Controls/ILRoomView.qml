import QtQuick 2.12
import QtQuick.Controls 2.12

Item {
    id: control

    width: 300
    height: 300

    property alias image: image.source
    property var currentLight: null

    Component {
        id: roomLight

        ILRoomLight {
        }
    }

    function addNewLight() {
        var light = roomLight.createObject(control)
        light.x = control.width / 2
        light.y = control.height / 2
        add(light)
    }

    function removeCurrentLight() {
        if (currentLight) {
            var index = _.lights.indexOf(currentLight)
            if (index < 0) {
                console.warn("currentLight not found in the list of lights!")
                return
            }

            _.lights.splice(index, 1)
            currentLight.destroy()
            currentLight = null
            _.configureCurrentLight()
        }
    }

    function add(light) {
        _.lights.push(light)
        light.toggled.connect(function() {
            currentLight = light.checked ? light : null
            _.configureCurrentLight()
        })
        light.dragTarget = control
    }

    QtObject {
        id: _
        property var lights: []

        function configureCurrentLight() {
            lights.forEach(function(light){
                if (light !== currentLight) {
                    light.checked = false
                }
            })
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
            currentLight = null
            _.configureCurrentLight()
        }
    }

    Component.onCompleted: {
        var lights = []
        for(var i = 0; i < children.length; ++i) {
            var child = children[i]
            if (child instanceof ILRoomLight) {
                lights.push(child)
            }
        }

        lights.forEach(function(light) {
            add(light)
        })
    }
}

