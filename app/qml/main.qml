import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "Constants"
import "Pages"
import "Pages/Login"
import "Pages/InitialSetup"

ApplicationWindow {
    id: window
    visible: true
    width: 360
//    width: 480
    height: 640
    title: qsTr("Initial Lights")

    function showOnboarding() {
        console.log("Onboarding")
        mainStackView.replace(null, onboardingView, StackView.Immediate)
    }

    function showLoginLobbyOrStartView() {
        if (!backend.user.isLogged) {
            showLoginLobbyView()
        } else {
            showStartView()
        }
    }

    function showLoginLobbyView() {
        mainStackView.replace(null, loginLobbyView, StackView.Immediate)
    }

    function showStartView() {
        if (backend.showInitialSetup) {
            mainStackView.replace(null, initialSetupManageRoomsView, StackView.Immediate)
        } else {
            mainStackView.replace(null, mainView, StackView.Immediate)
        }
    }

    StackView {
        id: mainStackView
        anchors.fill: parent
    }

    Component {
        id: onboardingView
        PageOnboarding {
            onDone: {
                backend.showOnboarding = false
                showLoginLobbyOrStartView()
            }
        }
    }

    Component {
        id: loginLobbyView
        PageLoginLobby {
            stackView: mainStackView
            user: backend.user
        }
    }

    Component {
        id: initialSetupManageRoomsView
        PageInitialSetupManageRooms {
            stackView: mainStackView
            rooms: backend.rooms
        }
    }

    Component {
        id: mainView
        PageMain {
            stackView: mainStackView
        }
    }

    Component.onCompleted: {
        if (backend.showOnboarding) {
            showOnboarding()
        } else {
            showLoginLobbyOrStartView()
        }
    }

    Connections {
        target: backend

        onShowOnboardingChanged: {
            if (backend.showOnboarding) {
                showOnboarding()
            }
        }
    }

    Connections {
        target: backend.user
        onIsLoggedChanged: showLoginLobbyOrStartView()
    }
}
