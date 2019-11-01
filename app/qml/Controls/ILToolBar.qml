import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0

import "../Constants"

ToolBar {

    implicitHeight: ILStyle.toolbarHeight

    Rectangle {
        anchors.fill: parent
        color: ILStyle.toolbarBackgroundColor
    }

    layer.enabled: true
    layer.effect: DropShadow {
        verticalOffset: 1
        color: ILStyle.toolbarShadowColor
        samples: 9
        radius: 4
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
