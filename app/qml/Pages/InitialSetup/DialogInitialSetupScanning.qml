import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../../Constants"
import "../../Controls"

Dialog {
    id: root

    implicitWidth: 360
    implicitHeight: 640

    ColumnLayout {
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: 130

        Image {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            source: "../../Images/Illustration-Floor-Plan.svg"
            sourceSize.width: 180
            sourceSize.height: 144
        }

        ILTitleText {
            text: qsTr("Scanning your space…")
            Layout.topMargin: 50
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
        }

        ILInfoText {
            text: qsTr("This can take a bit more depending on your space.")
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
        }
    }

    ILInfoText {
        text: qsTr("OUR TIPS:\nChange the default lights and controller names to easy understand them")
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        size: ILInfoText.Size.Small
    }
}
