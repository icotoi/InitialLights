import QtQuick 2.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

Item {
    id: element
    width: 400
    height: 400
    property alias gridLayout: gridLayout

    ColumnLayout {
        id: columnLayout
        height: 100
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top

        RowLayout {
            id: rowLayout
            width: 100
            height: 100
            Layout.fillWidth: true

            Button {
                text: qsTr("Button")
                Layout.fillWidth: true
            }

            Button {
                text: qsTr("Button")
                checkable: true
                Layout.fillWidth: true
            }
        }

        GridLayout {
            id: gridLayout
            Layout.fillWidth: true
            columns: 3
        }
    }

}

/*##^## Designer {
    D{i:1;anchors_width:100}
}
 ##^##*/
