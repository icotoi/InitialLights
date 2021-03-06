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
    property bool showHamburgerMenu: backend.isUserLogged

    function updateToolbarForCurrentItem() {
        extraToolbarItems.children = stackView.currentItem.extraToolbarItems
                ? stackView.currentItem.extraToolbarItems
                : []
        toolbarLabel.text = stackView.currentItem.title
                ? stackView.currentItem.title
                : window.title
    }

    function showOnboarding() {
        header.visible = false
        drawer.interactive = false
        drawer.enabled = false
        stackView.replace(null, onboardingView, StackView.Immediate)
    }

    function updateStartView() {
        header.visible = true
        if (!backend.isUserLogged) {
            drawer.interactive = false
            drawer.visible = false
            drawer.enabled = false
            stackView.replace(null, loginView, StackView.Immediate)
        } else {
            drawer.interactive = true
            drawer.enabled = true
            stackView.replace(null, mainView, StackView.Immediate)
        }
        updateToolbarForCurrentItem()
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
                enabled: showHamburgerMenu || !onStartPage
                icon.source: onStartPage ? (showHamburgerMenu ? ILStyle.hamburgerIconSource : "") : ILStyle.backIconSource
                onClicked: {
                    if (onStartPage && showHamburgerMenu) {
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
                showPage(roomView, { room: backend.rooms.get(index) })
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
                showPage(lightListView, {})
            }

            isOnlineSwitch {
                checked: backend.controllerList.isOnline
                onClicked: backend.controllerList.isOnline = isOnlineSwitch.checked
            }

            logout.onClicked: {
                backend.logout()
            }
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent
//        initialItem: mainView
    }

    Component {
        id: mainView
        PageMain {
            rooms: backend.mainPage.rooms
            sceneCount: backend.mainPage.sceneCount
            onTurnAll: backend.mainPage.turnAllLights(checked)
            onRoomClicked: backend.mainPage.turnLights(index, checked)
            onSceneClicked: backend.controllerList.turnScene(index, checked)
        }
    }

    Component {
        id: roomListView
        PageRoomList {
            model: backend.rooms

            addRoomButton.onClicked: backend.addNewRoom()

            onShowRoom: {
                stackView.push(roomView, { room: backend.rooms.get(index) })
                updateToolbarForCurrentItem()
            }
        }
    }

    Component {
        id: roomView
        PageRoom {
            stack: stackView
            lights: backend.lights
            onUpdateMainToolbar: updateToolbarForCurrentItem()
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
                stackView.push(lightListView)
                updateToolbarForCurrentItem()
            }

            clearLocalData.onClicked: {
                backend.clearLocalData()
            }

            reloadDemoData.onClicked: {
                backend.clearLocalData()
                backend.loadLocalData()
                backend.controllerList.isOnline = false
            }

            isOnlineSwitch {
                checked: backend.controllerList.isOnline
                onClicked: backend.controllerList.isOnline = isOnlineSwitch.checked
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
                onClicked: {
                    backend.controllerList.isOnline = true
                    backend.controllerList.scan()
                }
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
            stack: stackView
            property var extraToolbarItems: [
                refreshButton
            ]
            ToolButton {
                id: refreshButton
                icon.source: ILStyle.refreshControllerLightConfigurationSource
                onClicked: controller.connectToController()
                enabled: controller !== null ? !controller.isBusy : false
            }
            onUpdateMainToolbar: updateToolbarForCurrentItem()
        }
    }

    Component {
        id: lightListView
        PageLightList {
            property string title: qsTr("Lights")
            model: backend.lights
            stack: stackView
            onUpdateMainToolbar: updateToolbarForCurrentItem()
        }
    }

    Component {
        id: onboardingView
        PageOnboarding {
            onDone: {
                backend.showOnboarding = false
                updateStartView()
            }
        }
    }

    Component {
        id: registerNewUserView
        PageRegisterNewUser {
            property string title: qsTr("Register")
            onDone: backend.registerNewUser(user, password, fullName)
        }
    }

    Component {
        id: resetPasswordView
        PageResetPassword {
            property string title: qsTr("Lost password")
            onDone: backend.resetPassword(user)
        }
    }

    Component {
        id: loginView
        PageLogin {
            onResetPassword: {
                stackView.push(resetPasswordView)
                updateToolbarForCurrentItem()
            }

            onRegisterNewUser: {
                stackView.push(registerNewUserView)
                updateToolbarForCurrentItem()
            }

            onDone: backend.login(user, password)
        }
    }

    Component.onCompleted: {
        if (backend.showOnboarding) {
            showOnboarding()
        } else {
            updateStartView()
        }
//        showPage(settingsView, {})
//        showPage(lightListView, {})
//        var room = backend.rooms.get(0)
//        if (room !== null) {
//            stackView.push(roomView, { room: room })
//        }
    }

    Connections {
        target: backend

        onShowOnboardingChanged: {
            if (backend.showOnboarding) {
                showOnboarding()
            }
        }

        onIsUserLoggedChanged: {
            if (!backend.showOnboarding) {
                updateStartView()
            }
        }
    }
}
