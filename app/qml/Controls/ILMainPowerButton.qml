import QtQuick 2.12
import QtQuick.Controls 2.12

Item {
    id: control
    width: 400
    height: 100

    Rectangle {
        anchors.centerIn: parent
        implicitHeight: 50
        width: control.width + border.width * 2
        border.color: "black"
        border.width: 2
        color: "#060606"
        opacity: 0.5
    }

    Rectangle {
        width: 160
        height: width
        radius: width / 2
        color: "#303030"
        anchors.centerIn: parent
    }

    Button {
        id: button
        padding: 0
        rightPadding: 0
        bottomPadding: 0
        leftPadding: 0
        topPadding: 0
        checkable: true
        anchors.centerIn: parent
        implicitHeight: 100
        implicitWidth: 100

        background: Item {
            Image {
                anchors.centerIn: parent
                width: button.width
                height: width
            source: button.checked
                    ? "../Images/power_on.png"
                    : "../Images/power_off.png"
//            color: "red"
        }
        }
    }
}
