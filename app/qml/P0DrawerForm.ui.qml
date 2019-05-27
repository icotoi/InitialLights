import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    width: 400
    height: 400
    property alias roomsLayout: roomsLayout

    Flickable {
        id: flickable
        clip: true
        anchors.fill: parent
        contentHeight: columnLayout.height

        ColumnLayout {
            id: columnLayout
            width: flickable.width

            Label {
                id: label
                x: 0
                y: 41
                text: qsTr("Rooms")
            }

            Rectangle {
                id: rectangle
                height: 1
                color: "#ffffff"
                Layout.fillWidth: true
            }

            ColumnLayout {
                id: roomsLayout
                Layout.fillWidth: true
            }
        }
    }
}
