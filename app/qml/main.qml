import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "Constants"

ApplicationWindow {
    id: window
    visible: true
    width: 360
//    width: 480
    height: 640
    title: qsTr("Initial Lights")

    function showOnboarding() {
        console.log("Onboarding")
        stackView.replace(null, onboardingView, StackView.Immediate)
    }

    function showLoginLobbyOrStartView() {
        if (!backend.isUserLogged) {
            showLoginLobbyView()
        } else {
            showStartView()
        }
    }

    function showLoginLobbyView() {
        stackView.replace(null, loginLobbyView, StackView.Immediate)
    }

    function showStartView() {
    }

    StackView {
        id: stackView
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
            onLogin: console.log("TODO: login")
            onRegisterNewUser: console.log("TODO: register new user")
            onResetPassword: console.log("TODO: reset password")
//            onDone: backend.login(user, password)
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

        onIsUserLoggedChanged: showLoginLobbyOrStartView()
    }
}
