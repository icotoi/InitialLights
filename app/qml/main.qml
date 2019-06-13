import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

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
                icon.source: onStartPage
                             ? "Images/material.io-baseline-menu-24px.svg"
                             : "Images/material.io-baseline-arrow_back-24px.svg"
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

//            ToolButton {
//                icon.source: "Images/material.io-baseline-more_vert-24px.svg"
//            }
        }
    }

    Drawer {
        id: drawer
        y: header.height
        width: window.width * 0.6
        height: window.height - header.height
        PageDrawer {
            rooms: backend.rooms
            anchors.fill: parent

            onHomeClicked: {
                drawer.close()
                showHome()
            }

            onRoomClicked: {
                drawer.close()
                showPage(roomView, {
                             room: room,
                             title: room.name
                         })
            }

            onSettingsClicked: {
                drawer.close()
                showPage(controllerListView, {})
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
        id: controllerListView
        PageControllerList {
            property string title: qsTr("Controllers")
            property var extraToolbarItems: [
                bluetoothScanButton
            ]

            ToolButton {
                id: bluetoothScanButton
                icon.source: "Images/material.io-sharp-bluetooth_searching-24px.svg"
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
        PageController {}
    }

    Component.onCompleted: {
        showPage(controllerListView, {})
    }
}
