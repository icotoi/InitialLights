import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

import "../Constants"

Button {
    id: control

    text: "RGB + W"
    icon.source: "../Images/Controller-Icon-RGBW-Large.svg"
    font: Qt.font({ family: "Inter", styleName: "Medium", pointSize: 14 })

    contentItem: ColumnLayout {
        anchors.fill: parent
        Image {
            source: control.icon.source
            width: control.icon.width
            height: control.icon.height
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }

        Text {
            text: control.text
            wrapMode: Text.WordWrap
            Layout.fillHeight: true
            Layout.topMargin: 20
            Layout.fillWidth: true
            font: control.font
            opacity: enabled ? 1.0 : 0.3
            color: "#737F8C"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignTop
            elide: Text.ElideRight
        }
    }

    background: Rectangle {
        implicitWidth: 128
        implicitHeight: 128
        anchors.fill: parent
        opacity: enabled ? 1 : 0.3
        color: "#FFFFFF"
        border.color: control.checked ? "#0080FF" : "#E3E5E8"
        border.width: 1
        radius: 5

        layer.enabled: !control.down
        layer.effect: DropShadow {
            verticalOffset: 1
            color: "#2f5C6670"
            samples: 9
            radius: 4
        }
    }
}
