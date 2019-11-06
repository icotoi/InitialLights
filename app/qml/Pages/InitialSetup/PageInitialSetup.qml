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
            onBack: stackView.pop()
            onScan: {
                backend.controllers.scan()
                scanningDialog.open()
            }
        }
    }

    DialogInitialSetupScanning {
        id: scanningDialog
        modal: true

        property int border: 20

        width: root.width - 2 * border
        height: root.height - border

        x: border
        y: root.height

        enter: Transition {
            NumberAnimation { properties: "y"; to: scanningDialog.border; duration: 500 }
        }

        exit: Transition {
            NumberAnimation { properties: "y"; to: root.height; duration: 500 }
        }
    }

    Connections {
        target: backend.controllers

        onScanFinished: {
            scanningDialog.close()
        }
    }
}
