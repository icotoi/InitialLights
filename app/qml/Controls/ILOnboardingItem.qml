import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Item {
    property alias image: image.source
    property alias title: title.text
    property alias message: message.text

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent

        Image {
            id: image
            Layout.fillHeight: true
            Layout.fillWidth: true
            fillMode: Image.PreserveAspectFit
            source: "qrc:/qtquickplugin/images/template_image.png"
        }

        ILTitleLabel {
            id: title
            text: qsTr("Title")
        }

        Label {
            id: message
            text: qsTr("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nunc sed dui in nulla auctor volutpat vitae non sem. In hac.")
            rightPadding: 20
            leftPadding: 20
            bottomPadding: 20
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WordWrap
            font.pixelSize: 14
        }

    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:1;anchors_height:100;anchors_width:100;anchors_x:254;anchors_y:255}
}
##^##*/
