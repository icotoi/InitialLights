import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "Constants"
import "Pages"
import "Pages/Login"

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
        if (!backend.isUserLogged) {
            showLoginLobbyView()
        } else {
            showStartView()
        }
    }

    function showLoginLobbyView() {
        mainStackView.replace(null, loginLobbyView, StackView.Immediate)
    }

    function showStartView() {
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
