import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../Constants"
import "../Controls"

Page {
    id: root
    padding: 20

    implicitWidth: 360
    implicitHeight: 640

    Flickable {
        id: flickable
        enabled: !busyIndicator.running
        anchors.fill: parent
        contentHeight: columnLayout.height
        ScrollIndicator.vertical: ScrollIndicator {}

        ColumnLayout {
            id: columnLayout
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.left: parent.left

            Repeater {

                Layout.fillWidth: true

                model: backend ? backend.controllers.items : null

                delegate: ILControllerSetupDelegate {
                    Layout.fillWidth: true
                    name: model.name
                    address: model.address
                    controllerState: model.state
                    isOnline: model.isOnline
                    onClicked: root.clickedController(index)
                }
            }

            ILButton {
                text: "Search Controllers"
                Layout.fillWidth: true
                onClicked: {
                    busyIndicator.running = true
                    backend.bluetoothExplorer.search()
                }
            }

            ILButton {
                text: "Show Onboarding"
                Layout.fillWidth: true
                onClicked: backend.showOnboarding = true
            }

            ILButton {
                text: "Show Initial Setup"
                Layout.fillWidth: true
                onClicked: backend.showInitialSetup = true
            }

            ILButton {
                text: "Logout"
                Layout.fillWidth: true
                onClicked: backend.user.logout()
            }
        }
    }

    BusyIndicator {
        id: busyIndicator
        running: false
        visible: running
        anchors.centerIn: parent
    }

    Connections {
        target: backend ? backend.bluetoothExplorer : null
        onSearchFinished: busyIndicator.running = false
    }
}
