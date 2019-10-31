import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.12

import "Images"
import "Controls"
import "Constants"

Item {
    id: root

    property var room: null
    property alias model: listView.model

    property string title: "Add light" + (root.room !== null ? " to " + room.name : "")
    property var extraToolbarItems: []

    signal lightSelected(int index)

    ListView {
        id: listView
        anchors.fill: parent

        delegate: ItemDelegate {
            id: itemDelegate
            width: parent.width
            enabled: model.room === null
//            visible: model.room === null
//            height: visible ? implicitHeight : 0

            contentItem: ColumnLayout {
                Label {
                    id: nameLabel
                    text: model.name
                }

                Label {
                    property string controllerName: model.controller !== undefined
                                                    ? (model.controller.name !== ""
                                                       ? model.controller.name
                                                       : model.controller.address)
                                                    : "controller"
                    text: "<b>controller:</b> %1<br><b>type:</b> %2<br><b>room:</b> %3"
                    .arg(controllerName)
                    .arg(model.lightTypeName)
                    .arg(model.room !== null ? model.room.name : "<font color=\"tomato\">unassigned</font>")
                    font.pixelSize: nameLabel.font.pixelSize * 0.8
                }
            }

            onClicked: root.lightSelected(index)
        }
    }
}
