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

    function showOnboarding() {
    }

    function showLoginOrStartView() {
        if (!backend.isUserLogged) {
            showLoginView()
        } else {
            showStartView()
        }
    }

    function showLoginView() {
    }

    function showStartView() {
    }

    Component.onCompleted: {
        if (backend.showOnboarding) {
            showOnboarding()
        } else {
            showLoginOrStartView()
        }
    }

    Connections {
        target: backend

        onShowOnboardingChanged: {
            if (backend.showOnboarding) {
                showOnboarding()
            }
        }

        onIsUserLoggedChanged: showLoginOrStartView()
    }
}
