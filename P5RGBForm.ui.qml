import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    width: 600
    height: 400

    header: Label {
        text: qsTr("RGB")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    Label {
        text: qsTr("RGB")
        anchors.centerIn: parent

        ColorWheel {
            id: colorWheel
            x: -199
            y: -142
            width: 424
            height: 301
        }
    }
}
