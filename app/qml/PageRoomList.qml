import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "Images"
import "Controls"
import "Constants"

Item {
    id: root

    property alias model: listView.model

    signal showRoom(var room)

    ListView {
        id: listView
        anchors.fill: parent

        delegate: ItemDelegate {
            width: parent.width
            text: model.name
            onClicked: showRoom(model)
        }
    }
}
