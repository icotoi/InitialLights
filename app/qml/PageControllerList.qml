import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "Images"
import "Controls"
import "Constants"

Item {
    id: root

    property alias model: listView.model
    property bool isBusy: false
    property string message: ""

    signal showController(int index)

    ListView {
        id: listView
        anchors.fill: parent

        delegate: ILControllerItemDelegate {
            width: parent.width
            name: model.name
            address: model.address
            onClicked: showController(index)
        }
    }

    BusyIndicator {
        anchors.centerIn: parent
        visible: root.isBusy
    }

    Label {
        visible: root.message !== ""
        text: root.message
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        horizontalAlignment: Text.AlignHCenter

        background: Rectangle {
            color: "black"
            opacity: 0.2
        }
    }
}
