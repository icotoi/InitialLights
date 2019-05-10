import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Page {
    id: page
    width: 400
    height: 600

    header: Label {
        text: qsTr("RGB")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    ColumnLayout {
        anchors.fill: parent
        ColorWheel {
            id: colorWheel
            x: -199
            y: -142

            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
