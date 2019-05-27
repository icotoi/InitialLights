import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12

P2RoomForm {
    id: root

    property var title: "Room"

    property var extraToolbarItems: [
        deleteLightButton,
        addLightButton,
    ]

    Popup {
        id: popup

        x: (root.width - width) / 2
        y: root.height - height
        width: root.width - 50
        height: root.height - 90

        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

        LightColorChooserPopup {
            id: colorChooser
            anchors.fill: parent
            acceptButton.onClicked: {
                popup.close()
                roomView.currentLight.color = colorChooser.newColor
                colorRectangle.color = colorChooser.newColor
            }
        }
    }

    colorRectangleMouseArea.onClicked: {
        var color = roomView.currentLight.color
        colorChooser.oldColor = color
        colorChooser.newColor = color
        popup.open()
    }

    addLightButton.onClicked: roomView.addNewLight()
    deleteLightButton.onClicked: roomView.removeCurrentLight()

    onSwitch {
        onToggled: {
            if (roomView.currentLight) {
                roomView.currentLight.isOn = onSwitch.checked
            }
        }
    }

    intensitySlider {
        onValueChanged: {
            if (roomView.currentLight) {
                roomView.currentLight.lightIntensity = intensitySlider.value
            }
        }
    }

    temperatureSlider {
        onValueChanged: {
            if (roomView.currentLight) {
                roomView.currentLight.lightTemperature = temperatureSlider.value
            }
        }
    }

    configurationPane.visible: roomView.currentLight !== null

    roomView {
        onCurrentLightChanged: {
            if (roomView.currentLight !== null) {
                intensitySlider.value = roomView.currentLight.lightIntensity
                temperatureSlider.value = roomView.currentLight.lightTemperature
                onSwitch.checked = roomView.currentLight.isOn
                colorRectangle.color = roomView.currentLight.color
            }
        }
    }
}
