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

        delegate: ItemDelegate {
            width: parent.width

            contentItem: RowLayout {
                ColumnLayout {
                    Layout.fillWidth: true
                    Label {
                        Layout.fillWidth: true
                        text: "<b>Name:</b> " + model.name
                        elide: Text.ElideMiddle
                    }
                    Label {
                        Layout.fillWidth: true
                        text: "<b>Address:</b> " + model.address
                        elide: Text.ElideMiddle
                    }
                }

                ToolButton {
                    icon.source: "Images/material.io-baseline-arrow_forward_ios-24px.svg"
                    onClicked: showController(index)
                }
            }

            highlighted: ListView.isCurrentItem
            onClicked: listView.currentIndex = index
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
