import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import "../../Constants"
import "../../Controls"
import InitialLights 1.0

Page {
    id: root

    implicitWidth: 360
    implicitHeight: 640

    property var controllers: QtObject {
        property var items: ListModel{
            ListElement {
                name: "#1"
                address: "ACCF24634326FA12"
                isEnabled: true
                isOnline: true
                kind: Controller.RGBW
            }

            ListElement {
                name: "#2"
                address: "ACCF24634326FA13"
                isEnabled: false
                isOnline: true
                kind: Controller.RGBW
            }

            ListElement {
                name: "#3"
                address: "ACCF24634326FA13"
                isEnabled: true
                isOnline: false
                kind: Controller.RGBW
            }

            ListElement {
                name: "#4"
                address: "ACCF24634326FA13"
                isEnabled: false
                isOnline: false
                kind: Controller.RGBW
            }

            ListElement {
                name: "#5"
                address: "ACCF24634326FA14"
                isEnabled: true
                isOnline: true
                kind: Controller.Unknown
            }
        }
    }

    property var rooms

    property bool showScanningItem: !controllers || controllers.items.count === 0

    signal back()
    signal next()
    signal scan()
    signal clickedController(int index)

    background: Rectangle {
        color: ILStyle.backgroundColor
    }

    header: ILToolBar {
        id: iLToolBar

        ILToolBarBackButton {
            onClicked: back()
        }

        ILToolBarTitle {
            text: qsTr("Add your lights")
        }

        ILButton {
            text: qsTr("Next")
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            flat: true
            onClicked: next()
        }
    }

    Component {
        id: scanButton
        ILButton {
            text: qsTr("Scan for lights")
            highlighted: true
            onClicked: scan()
        }
    }

    Item {
        visible: showScanningItem
        anchors.fill: parent

        ColumnLayout {
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            Image {
                id: image
                Layout.bottomMargin: 25
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                source: "../../Images/Illustration-No-Lights-Defined.png"
            }

            ILInfoText {
                text: qsTr("Currently there are\nno lights added")
                horizontalAlignment: Text.AlignHCenter
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            }
        }

        Loader {
            sourceComponent: scanButton
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
        }
    }

    ListView {
        id: listView
        visible: !showScanningItem

        spacing: 12
        anchors.fill: parent
        anchors.rightMargin: 20
        anchors.leftMargin: 20

        header: ColumnLayout {
            anchors.right: parent.right
            anchors.left: parent.left

            ILTitleText {
                text: qsTr("%1 new controllers found").arg(controllers ? controllers.items.count : 0)
                horizontalAlignment: Text.AlignHCenter
                Layout.fillWidth: true
                Layout.topMargin: 20
                size: ILStyle.TextSize.Medium
            }

            ILInfoText {
                text: qsTr("In order to add the lights first make sure that all controllers are enabled")
                Layout.bottomMargin: 20
                horizontalAlignment: Text.AlignHCenter
                Layout.fillWidth: true
                size: ILStyle.TextSize.Medium
            }
        }

        model: controllers ? controllers.items : null

        delegate: ILControllerSetupDelegate {
            anchors.right: parent.right
            anchors.left: parent.left
            name: model.name
            address: model.address
            kind: model.kind
            isOnline: model.isOnline
            isEnabled: model.isEnabled
            onClicked: root.clickedController(index)
        }

        footer: ColumnLayout {
            anchors.right: parent.right
            anchors.left: parent.left
            Loader {
                Layout.bottomMargin: 20
                Layout.topMargin: 20
                Layout.fillWidth: true
                sourceComponent: scanButton
            }
        }
    }
}
