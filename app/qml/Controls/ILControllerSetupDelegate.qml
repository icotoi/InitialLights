import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import "../Constants"
import InitialLights 1.0

Rectangle {
    id: root

    property string name: "Unnamed"
    property string address: "ACCF24634326FA12"
    property bool isOnline: false
    property var controllerState

    signal clicked()

    implicitHeight: 60
    implicitWidth: 360

    color: isOnline
           ? (controllerState === Controller.NotConfigured ? "#F3F4F5" : "#FFFFFF")
           : "#f7eded"
    border.color: isOnline
                  ? "#E3E5E8"
                  : "#ffd4d4"
    radius: 4

    RowLayout {
        anchors.fill: parent
        Image {
            Layout.rightMargin: 16
            Layout.leftMargin: 16
            source: isOnline
                    ? (controllerState === Controller.NotConfigured
                       ? "../Images/Controller-Disabled.svg"
                       : "../Images/Controller-Enabled.svg" )
                    : "../Images/Controller-Offline.svg"
        }

        ColumnLayout {
            Layout.fillWidth: true
            Text {
                text: name
                Layout.fillWidth: true
                font: Qt.font({ family: "Inter", styleName: "Medium", pointSize: 14 })
                color: isOnline
                       ? "#000"
                       : "#ff2f2f"
            }
            Text {
                text: address
                Layout.fillWidth: true
                font: Qt.font({ family: "Inter", styleName: "Medium", pointSize: 12 })
                color: isOnline
                       ? "#5C6670"
                       : "#ff9090"
            }
        }

        Rectangle {
            Layout.leftMargin: 16
            Layout.rightMargin: 16

            implicitWidth: 100
            implicitHeight: 32
            color: isOnline
                   ? (controllerState === Controller.Enabled ? "#C2F2C2" : "#C7CCD2")
                   : "#ffafaf"

            border.color: isOnline
                          ? (controllerState === Controller.Enabled ? "#8AE68A" : "#ABB2BA")
                          : "#ff9090"
            border.width: 1
            radius: 4

            Text {
                anchors.centerIn: parent
                text: isOnline
                      ? (controllerState === Controller.Enabled
                         ? qsTr("ENABLED")
                         : (controllerState === Controller.Disabled ? qsTr("DISABLED") : qsTr("NOT CONFIGURED")))
                      : qsTr("OFFLINE")
                font: Qt.font({ family: "Inter", styleName: "Medium", pointSize: 10 })
                color: isOnline
                       ? (controllerState === Controller.Enabled ? "#21be2b" : "#fff")
                       : "#ff2f2f"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked()
    }
}
