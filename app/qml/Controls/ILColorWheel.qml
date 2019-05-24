import QtQuick 2.12
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.12

Item {
    id: control

    implicitHeight: 200
    implicitWidth: 200

    property real innerCircleScale: 0.6
    property int innerCircleMargin: 10

    property color borderColor: "#b0b0b0"
    property color warmWhiteColor: "#FBF4D6"
    property color coolWhiteColor: "#E6F5FA"

    property color labelColor: "#000000"
    property real labelTextScale: 0.1
    property real plusLabelTextScale: 1.5
    property string leftLabelText: qsTr("<b>WARM</b><br>Light")
    property string rightLabelText: qsTr("<b>COOL</b><br>Light")
    property bool useShaderWheel: false

    // internal
    QtObject {
        id: _

        property int innerCircleRadius: wheel.wheelSize * innerCircleScale * 0.5
        property int borderWidth: 2
        property real labelInnerSpacingScale: 1.0 / 20
    }

    ColorWheel {
        id: wheel
        useShader: useShaderWheel
        anchors.fill: parent
        anchors.margins: innerCircleMargin
    }

    Rectangle {
        width: wheel.wheelSize + _.borderWidth
        radius: width / 2
        height: width
        anchors.centerIn: wheel
        border.width: _.borderWidth
        border.color: borderColor
        color: "transparent"

        Rectangle {
            width: _.innerCircleRadius * 2
            height: width
            radius: width / 2
            color: warmWhiteColor
            anchors.centerIn: parent

            Canvas {
                anchors.fill: parent

                onPaint: {
                    var ctx = getContext("2d");
                    ctx.reset();

                    var centreX = width / 2;
                    var centreY = height / 2;

                    ctx.beginPath();
                    ctx.fillStyle = coolWhiteColor;
                    ctx.moveTo(centreX, centreY);
                    ctx.arc(centreX, centreY, width / 2, -Math.PI * 0.5, Math.PI * 0.5, false);
                    ctx.lineTo(centreX, centreY);
                    ctx.fill();

                    ctx.beginPath()
                    ctx.lineWidth = _.borderWidth
                    ctx.strokeStyle = borderColor
                    ctx.moveTo(centreX, 0)
                    ctx.lineTo(centreX, height)
                    ctx.stroke()
                }
            }
        }

        Rectangle {
            width: _.innerCircleRadius * 2 + _.borderWidth
            height: width
            radius: width / 2
            anchors.centerIn: parent
            border.width: _.borderWidth
            border.color: borderColor
            color: "transparent"

            Label {
                id: labelLeft
                anchors {
                    verticalCenter: parent.verticalCenter
                    right: parent.right
                    rightMargin: parent.width / 2 + parent.width * _.labelInnerSpacingScale
                }

                color: labelColor
                text: leftLabelText
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: parent.width * labelTextScale
            }

            Label {
                anchors {
                    verticalCenter: parent.verticalCenter
                    left: parent.left
                    leftMargin: parent.width / 2 + parent.width * _.labelInnerSpacingScale
                }

                color: labelColor
                text: rightLabelText
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: labelLeft.font.pixelSize
            }

            Label {
                color: labelColor
                text: qsTr("<b>＋</b>")
                anchors.centerIn: parent
                font.pointSize: labelLeft.font.pixelSize * plusLabelTextScale
            }
        }
    }
}
