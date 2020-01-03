import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../../Constants"
import "../../Controls"

Page {
    id: root
    padding: 20

    implicitWidth: 360
    implicitHeight: 640

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: developerView
    }

    Component {
        id: developerView

        Flickable {
            id: flickable
            anchors.fill: parent
            contentHeight: columnLayout.height
            ScrollIndicator.vertical: ScrollIndicator {}

            ColumnLayout {
                id: columnLayout
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.left: parent.left

                ILButtonWithBusyIndicator {
                    text: "Search Controllers"
                    Layout.fillWidth: true
                    enabled: !busy && !continuosSearchSwitch.checked
                    busy: backend ? backend.bluetoothExplorer.isSearching : false
                    onClicked: {
                        backend.bluetoothExplorer.search()
                    }
                }

                RowLayout {
                    Text {
                        text: "Continuous Search"
                    }

                    Switch {
                        id: continuosSearchSwitch
                        checked: false
                    }

                    Timer {
                        id: continuosSearchTimer
                        repeat: true
                        triggeredOnStart: true
                        running: continuosSearchSwitch.checked
                        interval: 20000 // in msec
                        onTriggered: if (backend) backend.bluetoothExplorer.search()
                    }
                }

                Repeater {

                    Layout.fillWidth: true

                    model: backend ? backend.controllers.items : null

                    delegate: ILControllerSetupDelegate {
                        Layout.fillWidth: true
                        name: model.name
                        address: model.address
                        kind: model.kind
                        isOnline: model.isOnline
                        isEnabled: model.isEnabled
                        onClicked: stackView.push(controllerConfigurationView,
                                                  { "controller" : backend.controllers.items.get(index)},
                                                  StackView.Immediate)
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
    }

    Component {
        id: controllerConfigurationView
        PageDeveloperControllerConfiguration {
            onCanceled: stackView.pop(StackView.Immediate)
        }
    }
}
