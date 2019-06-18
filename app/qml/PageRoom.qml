import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtMultimedia 5.12

PageRoomForm {
    id: root

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

    lightView.visible: false

    Component {
        id: lightSelectionView
        PageLightSelection {
            model: root.lights
            onLightSelected: {
                if (root.room !== null)
                    light.room = root.room
                stackView.pop()
                root.updateMainToolbar()
            }
        }
    }

    ToolButton {
        id: addLightButton
        icon.source: "Images/material.io-sharp-add-24px.svg"
        onClicked: {
            if (stackView === null)
                return;

            stackView.push(lightSelectionView, { room: root.room })
            root.updateMainToolbar()
        }
    }

    ToolButton {
        id: deleteLightButton
        icon.source: "Images/material.io-sharp-delete-24px.svg"
        visible: lightView.visible
        onClicked: roomView.removeCurrentLight()
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
}
