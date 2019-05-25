import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Item {
    id: control
    width: 400
    height: 100

    //////////////////////
    // horizontal indent
    property int horizontalIndentHeight: 50
    property color horizontalIndentColor: "#060606"
    property int horizontalIndentBorderWidth: 2
    property color horizontalIndentBorderColor: "black"

    ////////////////////
    // buttonRoundMask
    property int buttonRoundMaskSize: 160
    property color buttonRoundMaskColor: Material.background

    ///////////
    // button
    property int buttonSize: 100
    property url buttonOffImage: "../Images/power_off.png"
    property url buttonOnImage: "../Images/power_on.png"

    Rectangle {
        id: horizontalIndent
        anchors.centerIn: parent
        implicitHeight: control.horizontalIndentHeight
        width: control.width + border.width * 2
        border.color: control.horizontalIndentBorderColor
        border.width: control.horizontalIndentBorderWidth
        color: control.horizontalIndentColor
        opacity: 0.5
    }

    Rectangle {
        id: buttonRoundMask
        width: control.buttonRoundMaskSize
        height: width
        radius: width / 2
        anchors.centerIn: parent
        color: control.buttonRoundMaskColor
    }

    Button {
        id: button
        checkable: true
        anchors.centerIn: parent
        implicitHeight: control.buttonSize
        implicitWidth: control.buttonSize

        background: Item {
            Image {
                anchors.centerIn: parent
                width: button.width
                height: width
            source: button.checked
                    ? control.buttonOnImage
                    : control.buttonOffImage
        }
        }
    }
}
