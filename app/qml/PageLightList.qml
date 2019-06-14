import QtQuick 2.12
import QtQuick.Controls 2.12

Item {

    property alias model: listView.model

    ListView {
        id: listView
        anchors.fill: parent

        delegate: Column {
            width: parent.width
            property var controller: model.controller
            property var controllerId: controller ? (controller.name !== "" ? controller.name : controller.address) : "<?>"
            Label {
                text: "%1.%2 <%3>".arg(parent.controllerId).arg(model.name).arg(model.lightTypeName)
                elide: Text.ElideLeft
            }
        }
    }

}
