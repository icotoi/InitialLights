import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Layouts 1.13
import QtQuick.Controls 2.13

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent

        Image {
            id: image
            fillMode: Image.PreserveAspectFit
            Layout.fillHeight: true
            Layout.fillWidth: true
            source: camera.imagePath == "" ? "" : "file:" + camera.imagePath
        }

        Button {
            id: button
            text: qsTr("Launch Camera Intent")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            onClicked: camera.captureImage()
        }
    }
}
