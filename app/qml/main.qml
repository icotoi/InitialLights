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

    header: ToolBar {
        RowLayout {
            anchors.fill: parent

            // a hamburger button that rotates
            ToolButton {
                id: hamburgerButton
                text: onStartPage ? qsTr("☰") : qsTr("‹")
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
                text: qsTr("⋮")
//                onClicked: menu.open()
            }
        }
    }

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

    function showRoom(roomName) {
        toolbarLabel.text = roomName
        stackView.push(roomView)
        stackView.currentItem.title = roomName
        updateToolbarForCurrentItem()
    }

    Drawer {
        id: drawer
        y: header.height
        width: window.width * 0.6
        height: window.height - header.height
        P0Drawer {
            anchors.fill: parent
            onRoomClicked: {
                drawer.close()
                showRoom(room.text)
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
        showRoom("Test")
    }
}
