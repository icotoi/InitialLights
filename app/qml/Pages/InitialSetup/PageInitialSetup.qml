import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../../Constants"
import "../../Controls"

Page {
    id: root

    implicitWidth: 360
    implicitHeight: 640

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: roomsView
    }

    Component {
        id: roomsView
        PageInitialSetupManageRooms {
            rooms: backend.rooms
            onNext: stackView.push(lightsView)
        }
    }

    Component {
        id: lightsView
        PageInitialSetupManageRoomLights {
            rooms: backend.rooms
            onBack: stackView.pop()
        }
    }
}
