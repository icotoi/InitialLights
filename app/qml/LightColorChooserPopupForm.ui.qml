import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "Images"
import "Controls"
import "Constants"

Item {
    property color oldColor: "red"
    property alias newColor: colorWheel.color
    property alias oldColorMouseArea: oldColorMouseArea
    property alias acceptButton: acceptButton

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent

        ILColorWheel {
            id: colorWheel
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: oldColor
        }

        RowLayout {
            id: rowLayout
            width: 100
            height: 100

            Rectangle {
                color: oldColor
                width: ILStyle.colorRectangle.size
                height: width
                radius: ILStyle.colorRectangle.radius
                border.width: ILStyle.colorRectangle.borderWidth
                border.color: ILStyle.colorRectangle.borderColor

                MouseArea {
                    id: oldColorMouseArea
                    anchors.fill: parent
                }
            }

            Rectangle {
                id: newColor
                width: ILStyle.colorRectangle.size
                height: width
                radius: ILStyle.colorRectangle.radius
                border.width: ILStyle.colorRectangle.borderWidth
                border.color: ILStyle.colorRectangle.borderColor
                color: colorWheel.color
            }

            Item {
                Layout.fillWidth: true
            }

            Button {
                id: acceptButton
                text: qsTr("Accept")
            }
        }
    }
}






/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
