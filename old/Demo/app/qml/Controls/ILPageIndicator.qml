import QtQuick 2.12
import QtQuick.Controls 2.12

PageIndicator {
    id: control
    count: 5
    currentIndex: 2

    property color currentItemColor: "#056CF9"
    property color itemColor: "#000"

    delegate: Rectangle {
        implicitWidth: index == control.currentIndex ? 18 : 12
        implicitHeight: 12

        radius: height / 2
        border.color: index == control.currentIndex
         ? control.currentItemColor : itemColor
        border.width: 2
        color: index == control.currentIndex ? currentItemColor : "transparent"

        opacity: index === control.currentIndex ? 0.95 : pressed ? 0.7 : 0.45

        Behavior on opacity {
            OpacityAnimator {
                duration: 100
            }
        }
    }
}
