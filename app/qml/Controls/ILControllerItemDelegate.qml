import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

ItemDelegate {
    id: control

    property string name: "<name>"
    property string address: "<address>"

    contentItem: RowLayout {
        spacing: control.spacing

        ColumnLayout {
            Layout.fillWidth: true
            Label {
                id: nameLabel
                Layout.fillWidth: true
                text: "<b>Name:</b> " + control.name
                elide: Text.ElideMiddle
            }
            Label {
                Layout.fillWidth: true
                text: "<b>Address:</b> " + control.address
                elide: Text.ElideMiddle
            }
        }
    }
}
