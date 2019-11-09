import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Item {
    id: control

    property alias stepId: stepId.stepId
    property alias highlighted: stepId.highlighted
    property alias title: titleText.text
    property alias info: infoText.text
    property alias stepLine: stepLine

    default property alias contents: columnLayout.children

    implicitHeight: columnLayout.height
    opacity: enabled ? 1 : 0.3

    Rectangle {
        id: stepLine
        width: 1
        color: "#DFE1E6"
        anchors.bottom: parent.bottom
        anchors.top: stepId.verticalCenter
        anchors.left: stepId.horizontalCenter
    }

    ILConfigurationStepId {
        id: stepId
        anchors.leftMargin: 4
        anchors.top: parent.top
        anchors.left: parent.left
        Layout.alignment: Qt.AlignTop
    }

    ColumnLayout {
        id: columnLayout
        anchors.leftMargin: 40
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        Layout.alignment: Qt.AlignTop
        Layout.fillWidth: true
        Text {
            id: titleText
            text: "Title"
            Layout.fillWidth: true
            wrapMode: Text.WordWrap
            font: Qt.font({ family: "Inter", styleName: "Medium", pointSize: 16 })
        }

        Text {
            id: infoText
            text: "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nunc sed dui in nulla auctor volutpat vitae non sem. In hac."
            textFormat: Text.RichText
            Layout.fillWidth: true
            wrapMode: Text.WordWrap
            font: Qt.font({ family: "Inter", styleName: "Medium", pointSize: 12 })
            color: "#ABB2BA"
        }
    }
}

/*##^##
Designer {
    D{i:0;height:55;width:320}
}
##^##*/
