import QtQuick 2.12
import QtQuick.Controls 2.12

P2RoomForm {
    id: root

    property var selectedLight: null

    property var buttons: [
        iLCircularToggleLedButton0,
        iLCircularToggleLedButton1,
        iLCircularToggleLedButton2
    ]

    function configureSelectedLight() {
        buttons.forEach(function(button){
            if (button !== selectedLight) {
                button.checked = false
            }
        })

        if (selectedLight == null || !selectedLight.checked) return;

        intensitySlider.value = selectedLight.lightIntensity
        temperatureSlider.value = selectedLight.lightTemperature
        onSwitch.checked = selectedLight.isOn
    }

    imageMouseArea {
        onClicked: {
            selectedLight = null
            configureSelectedLight()
        }
    }

    onSwitch {
        onToggled: {
            if (selectedLight) {
                selectedLight.isOn = onSwitch.checked
            }
        }
    }

    intensitySlider {
        onValueChanged: {
            if (selectedLight) {
                selectedLight.lightIntensity = intensitySlider.value
            }
        }
    }

    temperatureSlider {
        onValueChanged: {
            if (selectedLight) {
                selectedLight.lightTemperature = temperatureSlider.value
            }
        }
    }

    configurationPane.visible: buttons.some(function(button) { return button.checked })

    Component.onCompleted: {
        buttons.forEach(function(button) {
            button.toggled.connect(function() {
                selectedLight = button
                configureSelectedLight()
            })
        })
    }
}
