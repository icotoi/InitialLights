import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

ListView {
    id: listView

    signal showController(int index)

    delegate: ItemDelegate {
        id: delegateItem

        width: parent.width

        contentItem: RowLayout {
            ColumnLayout {
                Layout.fillWidth: true
                Label {
                    Layout.fillWidth: true
                    text: "<b>Name:</b> " + model.info.name
                    elide: Text.ElideMiddle
                }
                Label {
                    Layout.fillWidth: true
                    text: "<b>Address:</b> " + model.info.address
                    elide: Text.ElideMiddle
                }
            }

            ToolButton {
                icon.source: "images/material.io--baseline-arrow_forward_ios-24px.svg"
                onClicked: showController(delegateItem.index)
            }
        }

        highlighted: ListView.isCurrentItem
        onClicked: listView.currentIndex = index
    }
}
