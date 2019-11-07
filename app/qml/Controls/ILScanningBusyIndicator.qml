import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../Constants"
import "../Controls"

BusyIndicator {
    id: control

    running: true

    background: Item {
        id: element
        implicitWidth: 220
        implicitHeight: 160

        Image {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            source: "../Images/Illustration-Floor-Plan.svg"
            sourceSize.width: 180
            sourceSize.height: 144
        }
    }

    contentItem: Item {
        anchors.horizontalCenter: parent.horizontalCenter
        Image {
            id: scanningItem
            source: "../Images/Illustration-Scanning-Item.svg"
            sourceSize.width: 200
            sourceSize.height: 66
            opacity: control.running ? 1 : 0
            anchors.horizontalCenter: parent.horizontalCenter

            Behavior on opacity {
                OpacityAnimator {
                    duration: 250
                }
            }

            SequentialAnimation {
                running: control.visible && control.running
                loops: Animation.Infinite

                PropertyAction {
                    target: scanningItem
                    property: "rotation"
                    value: 0
                }

                YAnimator {
                    target: scanningItem
                    from: -scanningItem.height / 2
                    to: control.height - scanningItem.height / 2
                    duration: 1000
                }

                PropertyAction {
                    target: scanningItem
                    property: "rotation"
                    value: 180
                }

                YAnimator {
                    target: scanningItem
                    from: control.height - scanningItem.height / 2
                    to: -scanningItem.height / 2
                    duration: 1000
                }
            }
        }
    }
}

