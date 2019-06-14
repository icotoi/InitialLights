import QtQuick 2.12
import QtQuick.Controls 2.12

Label {
    property color backgroundColor: "lightBlue"

    text: "section title"
    padding: 5
    font.bold: true
    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignHCenter

    background: Rectangle {
        color: backgroundColor
        opacity: 0.2
    }
}
