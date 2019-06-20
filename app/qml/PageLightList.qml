import QtQuick 2.12
import QtQuick.Controls 2.12

import "Controls"

Item {
    id: root

    property var stack: null
    property alias model: listView.model

    signal updateMainToolbar()

    Component {
        id: colorSelectionView
        PageColorSelection {
            property var light: null
            Component.onDestruction: {
                if (light !== null) {
                    light.color = selectedColor
                }
            }
        }
    }

    ListView {
        id: listView
        anchors.fill: parent

        delegate: ILLight {
            width: parent.width
            controllerName: model.controller !== undefined
                            ? (model.controller.name !== ""
                               ? model.controller.name
                               : model.controller.address)
                            : "controller"
            light: listView.model.get(index)
            enabled: (light !== null && light.controller !== null) ? !light.controller.isBusy : false

            onColorSwatchClicked: {
                if (root.stack === null)
                    return;

                root.stack.push(colorSelectionView, { inputColor: color, light: listView.model.get(index) })
                root.updateMainToolbar()
            }
        }
    }
}
