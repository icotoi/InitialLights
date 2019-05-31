import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Layouts 1.13
import QtQuick.Controls 2.13

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Demo Android Intents Photos")

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent

        Image {
            id: image
            fillMode: Image.PreserveAspectFit
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Button {
            id: button
            text: qsTr("Select a photo")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            onClicked: photos.selectImage()
        }
    }
}
