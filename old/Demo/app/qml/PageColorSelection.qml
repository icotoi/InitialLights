import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.12

import "Images"
import "Controls"
import "Constants"

Item {
    id: root

    property string title: qsTr("Select a color")
    property color inputColor: "white"
    property alias selectedColor: colorWheel.color

    Component {
        id: colorSwatch
        Rectangle {
            implicitHeight: 50
            implicitWidth: 50
            color: parent.color
            border.color: "lightGray"
            border.width: 1
            radius: 5
            MouseArea {
                anchors.fill: parent
                onClicked: colorWheel.color = parent.color
            }
        }
    }

    ColumnLayout {
        anchors.rightMargin: 8
        anchors.leftMargin: 8
        anchors.bottomMargin: 8
        anchors.topMargin: 8
        anchors.fill: parent
        ILColorWheel {
            id: colorWheel
            color: root.inputColor
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Loader {
                sourceComponent: colorSwatch
                property color color: root.inputColor
                Layout.fillWidth: false
            }
            Loader {
                sourceComponent: colorSwatch
                property color color: colorWheel.warmWhiteColor
                Layout.fillWidth: false
            }
            Loader {
                sourceComponent: colorSwatch
                property color color: colorWheel.coolWhiteColor
                Layout.fillWidth: false
            }
        }
    }
}
