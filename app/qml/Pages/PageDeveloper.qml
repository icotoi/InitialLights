import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../Constants"
import "../Controls"

Page {
    id: root
    padding: 20

    signal showOnboarding()
    signal showInitialSetup()
    signal logout()

    implicitWidth: 360
    implicitHeight: 640

    Flickable {
        anchors.fill: parent
        contentHeight: columnLayout.height
        ScrollIndicator.vertical: ScrollIndicator {}

        ColumnLayout {
            id: columnLayout
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.left: parent.left

            ILButton {
                text: "Show Onboarding"
                Layout.fillWidth: true
                onClicked: showOnboarding()
            }

            ILButton {
                text: "Show Initial Setup"
                Layout.fillWidth: true
                onClicked: showInitialSetup()
            }

            ILButton {
                text: "Logout"
                Layout.fillWidth: true
                onClicked: logout()
            }
        }
    }
}
