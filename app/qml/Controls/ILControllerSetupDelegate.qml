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


    implicitHeight: 60
    implicitWidth: 360
    border.color: "#E3E5E8"
    radius: 4

    RowLayout {
        anchors.fill: parent
        Image {
            Layout.rightMargin: 16
            Layout.leftMargin: 16
            source: "../Images/Controller-Enabled.svg"
        }

        ColumnLayout {
            Layout.fillWidth: true
            Text {
                text: name
                Layout.fillWidth: true
                font: nameFont
            }
            Text {
                text: address
                Layout.fillWidth: true
                font: addressFont
                color: addressColor
            }
        }

        Button {
            id: enableControllerButton
            Layout.leftMargin: 16
            Layout.rightMargin: 16
            checkable: true

            contentItem: Text {
                text: enableControllerButton.checked ? qsTr("ENABLED") : qsTr("DISABLED")
                font: enableControllerButton.font
                opacity: enabled ? 1.0 : 0.3
                color: enableControllerButton.checked ? "#21be2b" : "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }

            background: Rectangle {
                implicitWidth: 84
                implicitHeight: 32
                opacity: enabled ? 1 : 0.3
                color: enableControllerButton.checked ? "#C2F2C2" : "#C7CCD2"
                border.color: enableControllerButton.checked ? "#8AE68A" : "#ABB2BA"
                border.width: 1
                radius: 4
            }
        }
    }
}


