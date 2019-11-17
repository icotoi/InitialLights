import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0

Rectangle {
    id: control

    property bool highlighted: false
    property string stepId: "1"

    implicitWidth: 24
    implicitHeight: 24

    radius: width / 2
    border.width: 2
    border.color: "#ffffff"
    color: highlighted ? "#0080FF" : "#ACB4BF"

    Text {
        text: stepId
        anchors.centerIn: parent
        font: Qt.font({ family: "Inter", styleName: "Medium", pointSize: 12 })
        color: "#ffffff"
    }

    layer.enabled: true
    layer.effect: DropShadow {
        verticalOffset: 1
        color: "#ACB4BF"
        samples: 9
        radius: 4
    }
}
