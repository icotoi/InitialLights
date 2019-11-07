import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import "../Constants"

Rectangle {
    id: root

    property string name: "Unnamed"
    property string address: "ACCF24634326FA12"

    property font nameFont: Qt.font({ family: "Inter", styleName: "Medium", pointSize: 14 })
    property font addressFont: Qt.font({ family: "Inter", styleName: "Medium", pointSize: 12 })
    property color addressColor: "#5C6670"

    property bool configured: false
    property bool online: true
    property bool controllerEnabled: false

    enabled: online

    implicitHeight: 60
    implicitWidth: 360
    color: online ? (configured ? "#FFFFFF" : "#F3F4F5") : "#f7eded"
    border.color: online ? "#E3E5E8" : "#ffd4d4"
    radius: 4

    RowLayout {
        anchors.fill: parent
        Image {
            Layout.rightMargin: 16
            Layout.leftMargin: 16
            source: online
                    ? ( configured ? "../Images/Controller-Enabled.svg" : "../Images/Controller-Disabled.svg")
                    : "../Images/Controller-Offline.svg"
        }

        ColumnLayout {
            Layout.fillWidth: true
            Text {
                text: name
                Layout.fillWidth: true
                font: nameFont
                color: online ? "black" : "#ff2f2f"
            }
            Text {
                text: address
                Layout.fillWidth: true
                font: addressFont
                color: online ? addressColor : "#ff9090"
            }
        }

        Button {
            enabled: configured
            id: enableControllerButton
            Layout.leftMargin: 16
            Layout.rightMargin: 16
            checkable: true
            checked: controllerEnabled
            onToggled: controllerEnabled = checked

            contentItem: Text {
                text: online
                      ? (configured && enableControllerButton.checked ? qsTr("ENABLED") : qsTr("DISABLED"))
                      : qsTr("DELETE")
                font: enableControllerButton.font
                color: online
                       ? (configured && enableControllerButton.checked ? "#21be2b" : "white")
                       : "#ff2f2f"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }

            background: Rectangle {
                implicitWidth: 84
                implicitHeight: 32
                color: online
                       ? (configured && enableControllerButton.checked ? "#C2F2C2" : "#C7CCD2")
                       : "#ffafaf"
                border.color: online
                              ? (configured && enableControllerButton.checked ? "#8AE68A" : "#ABB2BA")
                              : "#ff9090"
                border.width: 1
                radius: 4
            }
        }
    }
}


