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
    }

    function showRoom(roomName) {
        toolbarLabel.text = roomName

        switch (stackView.depth) {
        case 0:
        case 1:
            stackView.push(roomView)
            break
        case 2:
            stackView.replace(roomView)
            break
        default:
            stackView.pop(null)
            stackView.push(roomView)
            break
        }

        stackView.currentItem.title = roomName
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

            ToolButton {
                icon.source: "Images/material.io-baseline-more_vert-24px.svg"
            }
        }
    }

    Drawer {
        id: drawer
        y: header.height
        width: window.width * 0.6
        height: window.height - header.height
        P0Drawer {
            rooms: backend.rooms
            anchors.fill: parent
            onRoomClicked: {
                drawer.close()
                showRoom(room.name)
            }

            onHomeClicked: {
                drawer.close()
                showHome()
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
        P1Main {}
    }

    Component {
        id: roomView
        P2Room {}
    }

    Component.onCompleted: {
//        showRoom("Test")
    }
}
