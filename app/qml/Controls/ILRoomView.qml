import QtQuick 2.12
import QtQuick.Controls 2.12

Item {
    id: control

    width: 300
    height: 300

    property alias image: image.source
    property var currentLight: null

    function add(light) {
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
        for(var i = 0; i < children.length; ++i) {
            var child = children[i]
            if (child instanceof ILRoomLight) {
                _.lights.push(child)
            }
        }

        _.lights.forEach(function(light) {
            add(light)
        })
    }
}

