import QtQuick 2.12
import QtQuick.Controls 2.12

import "Controls"

Item {

    property alias model: listView.model

    ListView {
        id: listView
        anchors.fill: parent

        delegate: ILLight {
            width: parent.width
            controllerName: model.controller.name !== ""
                            ? model.controller.name
                            : model.controller.address
            light: model
        }
    }
}
