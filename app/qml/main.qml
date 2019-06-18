import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "Constants"

ApplicationWindow {
    id: window
    visible: true
    width: 360
    height: 640
    title: qsTr("Initial Lights")

    property bool onStartPage: stackView.depth == 1

    function updateToolbarForCurrentItem() {
        if (onStartPage) {
            extraToolbarItems.children = []
            toolbarLabel.text = window.title
        } else {
            extraToolbarItems.children = stackView.currentItem.extraToolbarItems
                    ? stackView.currentItem.extraToolbarItems
                    : []
            toolbarLabel.text = stackView.currentItem.title
                    ? stackView.currentItem.title
                    : window.title
        }
    }

    function showHome() {
        stackView.pop(null)
        updateToolbarForCurrentItem()
    }

    function showPage(view, options) {
        switch (stackView.depth) {
        case 0:
        case 1:
            stackView.push(view, options)
            break
        case 2:
            stackView.replace(view, options)
            break
        default:
            stackView.pop(null)
            stackView.push(view, options)
            break
        }
        updateToolbarForCurrentItem()
    }


    header: ToolBar {
        RowLayout {
            anchors.fill: parent

            // a hamburger button that rotates
            ToolButton {
                id: hamburgerButton
                icon.source: onStartPage ? ILStyle.hamburgerIconSource : ILStyle.backIconSource
                onClicked: {
                    if (onStartPage) {
                        drawer.visible ? drawer.close() : drawer.open()
                    } else {
                        stackView.pop()
                        updateToolbarForCurrentItem()
                    }
                }
                transform: Rotation {
                    origin {
                        x: hamburgerButton.width / 2
                        y: hamburgerButton.height / 2
                    }
                    angle: (onStartPage && drawer.visible) ? drawer.position * 90: 0
                }
            }

            Label {
                id: toolbarLabel
                text: window.title
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignLeading
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }

            RowLayout {
                id: extraToolbarItems
            }
        }
    }

    Drawer {
        id: drawer
        y: header.height
        width: window.width * 0.6
        height: window.height - header.height
        PageDrawer {
            rooms: backend.rooms
            scenes: backend.scenes
            anchors.fill: parent

            home.onClicked: {
                drawer.close()
                showHome()
            }

            roomList.onClicked: {
                drawer.close()
                showPage(roomListView, {})
            }

            onRoomClicked: {
                drawer.close()
                showPage(roomView, {
                             room: room,
                             title: room.name
                         })
            }

            settings.onClicked: {
                drawer.close()
                showPage(settingsView, {})
            }

            controllerList.onClicked: {
                drawer.close()
                showPage(controllerListView, {})
            }

            lightList.onClicked: {
                drawer.close()
                showPage(lightsListView, {})
            }
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: mainView
    }

    Component {
        id: mainView
        PageMain {}
    }

    Component {
        id: roomListView
        PageRoomList {
            property string title: qsTr("Rooms")
            model: backend.rooms

            onShowRoom: {
                stackView.push(roomView, {
                                   room: room,
                                   title: room.name
                               })
                updateToolbarForCurrentItem()
            }
        }
    }

    Component {
        id: roomView
        PageRoom {
            property string title: "Room"
            property var extraToolbarItems: [
                deleteLightButton,
                addLightButton,
                cameraButton,
                photosButton,
            ]
        }
    }

    Component {
        id: settingsView
        PageSettings {
            property string title: qsTr("Settings")

            roomList.onClicked: {
                stackView.push(roomListView)
                updateToolbarForCurrentItem()
            }

            controllerList.onClicked: {
                stackView.push(controllerListView)
                updateToolbarForCurrentItem()
            }

            lightList.onClicked: {
                stackView.push(lightsListView)
                updateToolbarForCurrentItem()
            }

            clearLocalData.onClicked: {
                backend.clearLocalData()
            }

            reloadDemoData.onClicked: {
                backend.clearLocalData()
                backend.loadLocalData()
            }
        }
    }

    Component {
        id: controllerListView
        PageControllerList {
            property string title: qsTr("Controllers")
            property var extraToolbarItems: [
                bluetoothScanButton
            ]

            ToolButton {
                id: bluetoothScanButton
                icon.source: ILStyle.bluetoothScanIconSource
                onClicked: backend.controllerList.scan()
                enabled: !backend.controllerList.isBusy
            }

            model: backend.controllerList.controllers
            isBusy: backend.controllerList.isBusy
            message: backend.controllerList.message

            onShowController: {
                stackView.push(controllerView, { controller: backend.controllerList.controllers.get(index) })
                updateToolbarForCurrentItem()
            }
        }
    }

    Component {
        id: controllerView
        PageController {
            property var extraToolbarItems: [
                refreshButton
            ]
            ToolButton {
                id: refreshButton
                icon.source: ILStyle.refreshControllerLightConfigurationSource
                onClicked: controller.connectToController()
                enabled: controller !== null ? !controller.isBusy : false
            }
        }
    }

    Component {
        id: lightsListView
        PageLightList {
            property string title: qsTr("Lights")
            model: backend.lights
        }
    }

//    Component.onCompleted: {
//        showPage(settingsView, {})
//        showPage(lightsListView, {})
//    }
}
