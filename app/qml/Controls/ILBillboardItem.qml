import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import "../Constants"

Item {
    id: element
    property alias image: image.source
    property alias title: title.text
    property alias message: message.text

    property int textHorizontalMargin: 20
    property int textTopMargin: 130

    implicitWidth: 360
    implicitHeight: 640

    Image {
        id: image
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        source: "../Images/background-onboarding-1.jpg"
    }

    ColumnLayout {
        id: columnLayout
        anchors.top: parent.top
        anchors.topMargin: textTopMargin
        anchors.right: parent.right
        anchors.rightMargin: textHorizontalMargin
        anchors.left: parent.left
        anchors.leftMargin: textHorizontalMargin

        ILTitleText {
            id: title
            Layout.fillWidth: true
        }

        ILInfoText {
            id: message
            Layout.fillWidth: true
        }
    }
}
