import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Item {
    id: element
    property alias image: image.source
    property alias title: title.text
    property alias message: message.text

    Image {
        id: image
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        source: "qrc:/qtquickplugin/images/template_image.png"
    }

    ColumnLayout {
        id: columnLayout
        anchors.top: parent.top
        anchors.topMargin: 100
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20

        spacing: 16

        Label {
            id: title
            text: qsTr("Title")
            Layout.fillWidth: true
            wrapMode: Text.WordWrap
            font.pixelSize: 24
            font.bold: true
        }

        Label {
            id: message
            text: qsTr("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nunc sed dui in nulla auctor volutpat vitae non sem. In hac.")
            Layout.fillWidth: true
            wrapMode: Text.WordWrap
            font.pixelSize: 20
            opacity: .8
        }

    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:640;width:360}
}
##^##*/
