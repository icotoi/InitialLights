import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import "../Constants"
import InitialLights 1.0

Rectangle {
    id: root

    property string name: "Unnamed"
    property string address: "ACCF24634326FA12"

    property var controllerState

    implicitHeight: 60
    implicitWidth: 360

    color: controllerState === Controller.Offline
           ? "#f7eded"
           : (controllerState === Controller.Unconfigured ? "#F3F4F5" : "#FFFFFF")
    border.color: controllerState === Controller.Offline
                  ? "#ffd4d4"
                  : "#E3E5E8"
    radius: 4

    RowLayout {
        anchors.fill: parent
        Image {
            Layout.rightMargin: 16
            Layout.leftMargin: 16
            source: controllerState === Controller.Offline
                    ? "../Images/Controller-Offline.svg"
                    : (controllerState === Controller.Unconfigured
                       ? "../Images/Controller-Disabled.svg"
                       : "../Images/Controller-Enabled.svg" )
        }

        ColumnLayout {
            Layout.fillWidth: true
            Text {
                text: name
                Layout.fillWidth: true
                font: Qt.font({ family: "Inter", styleName: "Medium", pointSize: 14 })
                color: controllerState === Controller.Offline ? "#ff2f2f" : "#000"
            }
            Text {
                text: address
                Layout.fillWidth: true
                font: Qt.font({ family: "Inter", styleName: "Medium", pointSize: 12 })
                color: controllerState === Controller.Offline ? "#ff9090" : "#5C6670"
            }
        }

        Rectangle {
            Layout.leftMargin: 16
            Layout.rightMargin: 16

            implicitWidth: 100
            implicitHeight: 32
            color: controllerState === Controller.Offline
                   ? "#ffafaf"
                   : (controllerState === Controller.Enabled ? "#C2F2C2" : "#C7CCD2")

            border.color: controllerState === Controller.Offline
                          ? "#ff9090"
                          : (controllerState === Controller.Enabled ? "#8AE68A" : "#ABB2BA")
            border.width: 1
            radius: 4

            Text {
                anchors.centerIn: parent
                text: controllerState === Controller.Offline
                      ? qsTr("OFFLINE")
                      : (controllerState === Controller.Enabled
                         ? qsTr("ENABLED")
                         : (controllerState === Controller.Disabled ? qsTr("DISABLED") : qsTr("NOT CONFIGURED")))
                font: Qt.font({ family: "Inter", styleName: "Medium", pointSize: 10 })
                color: controllerState === Controller.Offline
                       ? "#ff2f2f"
                       : (controllerState === Controller.Enabled ? "#21be2b" : "#fff")
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }
        }
    }
}
