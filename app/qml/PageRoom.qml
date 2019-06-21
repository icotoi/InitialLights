import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtMultimedia 5.12

import "Images"
import "Controls"
import "Constants"

Item {
    id: root

//    focus: true

    property var room: null
    property var lights: null
    property var stack: null

    property bool isCameraAvailable: QtMultimedia.availableCameras.length > 0
    property bool capturingImage: false

    property string title: room !== null ? room.name : "Room"
    property var extraToolbarItems: [
        deleteLightButton,
        addLightButton,
        cameraButton,
        photosButton,
    ]

    property alias deleteLightButton: deleteLightButton
    property alias cameraButton: cameraButton
    property alias photosButton: photosButton

    signal updateMainToolbar()

    clip: true

    Component {
        id: lightSelectionView
        PageLightSelection {
            model: root.lights
            onLightSelected: {
                if (root.room !== null) {
                    var light = root.lights.get(index)
                    light.room = root.room
                    roomView.currentIndex = root.room.lights.indexOf(light)
                }
                if (root.stack !== null) {
                    root.stack.pop()
                    root.updateMainToolbar()
                }
            }
        }
    }

    Component {
        id: colorSelectionView
        PageColorSelection {
            Component.onDestruction: {
                var light = lightConfigurator.light
                if (light !== null) {
                    light.color = selectedColor
                }
            }
        }
    }

    ToolButton {
        id: addLightButton
        icon.source: "Images/material.io-sharp-add-24px.svg"
        onClicked: {
            if (root.stack === null)
                return;

            root.stack.push(lightSelectionView, { room: root.room })
            root.updateMainToolbar()
        }
    }

    ToolButton {
        id: deleteLightButton
        icon.source: "Images/material.io-sharp-delete-24px.svg"
        visible: lightConfigurator.visible
        onClicked: {
            if (root.room === null || roomView.currentIndex < 0)
                return

            var light = root.room.lights.get(roomView.currentIndex)
            if (light !== null)
                light.room = null

            roomView.currentIndex = -1
        }
    }

    ToolButton {
        id: cameraButton
        icon.source: "Images/material.io-baseline-photo_camera-24px.svg"
        enabled: isCameraAvailable
        onClicked: capturingImage = !capturingImage
    }

    ToolButton {
        id: photosButton
        icon.source: "Images/material.io-baseline-photo_library-24px.svg"
        enabled: false // TODO: find out how to test if we can browse for photos
    }

    Camera {
        id: camera

        imageCapture {
            onImageCaptured: {
                // Show the preview in an Image
                roomView.image = preview
                capturingImage = false
            }
        }
    }

    ILRoomView {
        id: roomView

        y: 0
        width: 330
        height: 330
        anchors.horizontalCenter: parent.horizontalCenter
        lights: room !== null ? room.lights : null

        image: "Images/pixabay_illumination-lights-bulbs-731494_1920.jpg"
    }

    VideoOutput {
        visible: capturingImage
        source: camera
        focus : visible // to receive focus and capture key events when visible
        anchors.fill: roomView

        MouseArea {
            anchors.fill: parent;
            onClicked: camera.imageCapture.capture();
        }
    }

    Pane {
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        visible: (room !== null && roomView.currentIndex < 0)
        TextField {
            id: roomNameTextField
            focus: true
            anchors.fill: parent
            placeholderText: qsTr("Room Name")
            text: root.room !== null ? root.room.name : ""
            onEditingFinished: {
                if (root.room !== null) { root.room.name = roomNameTextField.text }
                root.updateMainToolbar()
            }
        }
    }

    Pane {
//        width: parent.width
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        visible: (room !== null && roomView.currentIndex >= 0)

        ILLight {
            id: lightConfigurator
            anchors.fill: parent
            light: (room !== null && roomView.currentIndex >= 0) ? room.lights.get(roomView.currentIndex) : null
            rgbChannelsVisible: true

            onColorSwatchClicked: {
                if (root.stack === null)
                    return;

                root.stack.push(colorSelectionView, { inputColor: color })
                root.updateMainToolbar()
            }
        }
    }
}
