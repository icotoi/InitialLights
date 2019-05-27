import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

P0DrawerForm {
    id: form

    signal roomClicked(var room)

    Component {
        id: roomButton
        Button {
            flat: true
            Layout.fillWidth: true
        }
    }

    function addRoom(label) {
        var button = roomButton.createObject(form, {"text": label})
        button.clicked.connect(function() { roomClicked(button) })
        roomsLayout.children.push(button)
    }

    Component.onCompleted: {
        for(var i = 0; i < 20; ++i) {
            addRoom("Room %1".arg(i))
        }
    }
}
