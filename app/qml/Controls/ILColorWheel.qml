import QtQuick 2.12
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.12

Item {
    id: control

    implicitHeight: 200
    implicitWidth: 200

    property real hue: 0.0

    property int borderWidth: 2
    property color borderColor: "#b0b0b0"

    ////////////////////
    // the color wheel
    // true: use the shader wheel
    // false: use the canvas wheel
    property alias useShaderWheel: wheel.useShader

    ///////////////////
    // the inner area
    property real innerCircleScale: 0.6 // wheel radius / inner circle radius

    property color warmWhiteColor: "#FBF4D6"
    property color coolWhiteColor: "#E6F5FA"

    property color labelColor: "#000000"
    property real labelTextScale: 0.1 // left & right font pixel size / inner circle width
    property real plusLabelTextScale: 1.5 // plus font size / left & right font size
    property string leftLabelText: qsTr("<b>WARM</b><br>Light")
    property string rightLabelText: qsTr("<b>COOL</b><br>Light")

    ///////////////
    // the picker
    property int pickerRadius: 10
    property color pickerColor: "white"
    property int pickerBorderWidth: 2
    property color pickerBorderColor: borderColor

    // internal properties not to be exported outside the control
    QtObject {
        id: _

        property int innerCircleRadius: wheel.wheelSize * innerCircleScale * 0.5
        property real labelInnerSpacingScale: 1.0 / 20

        property int trackOuterRadius: wheel.wheelSize * 0.5
        property int trackInnerRadius: trackOuterRadius * control.innerCircleScale
        property int trackRadius: (trackInnerRadius + trackOuterRadius) * 0.5
        property int trackWidth: trackOuterRadius - trackInnerRadius

        property real currentHue: -1
        property real initialHue: -1
    }

    ColorWheel {
        id: wheel
        useShader: false
        anchors.fill: parent
    }

    Rectangle {
        width: wheel.wheelSize + borderWidth
        radius: width / 2
        height: width
        anchors.centerIn: wheel
        border.width: borderWidth
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
                    ctx.lineWidth = borderWidth
                    ctx.strokeStyle = borderColor
                    ctx.moveTo(centreX, 0)
                    ctx.lineTo(centreX, height)
                    ctx.stroke()
                }
            }
        }

        Rectangle {
            width: _.innerCircleRadius * 2 + borderWidth
            height: width
            radius: width / 2
            anchors.centerIn: parent
            border.width: borderWidth
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

    Item {
        id: pickerCursor

        x: _.trackRadius * Math.cos(2 * Math.PI * hue - Math.PI) + control.width / 2 - r
        y: _.trackRadius * Math.sin(-2 * Math.PI * hue - Math.PI) + control.height / 2 - r

        property int r : _.trackWidth * 0.3
        property real hue: _.currentHue >= 0 ? _.currentHue : control.hue

        Rectangle {
            width: parent.r*2
            height: parent.r*2
            radius: parent.r
            border.color: control.pickerBorderColor
            border.width: control.pickerBorderWidth
            color: control.pickerColor
        }
    }

    MouseArea {
        id : wheelArea
        anchors.centerIn: wheel
        width: wheel.wheelSize
        height: wheel.wheelSize
        preventStealing: true

        function updateHue(mouse, area, minRadius, maxRadius) {
            // cartesian to polar coords
            var ro = Math.sqrt(Math.pow(mouse.x - area.width / 2, 2) + Math.pow(mouse.y - area.height / 2, 2));
            var theta = Math.atan2(-(mouse.y - area.height / 2), (mouse.x - area.width / 2)) + Math.PI;

            if (minRadius <= ro && ro <= maxRadius) {
                _.currentHue = theta / (2*Math.PI)
                control.hue = _.currentHue
            } else {
                _.currentHue = -1
                control.hue = _.initialHue
            }
        }

        onPositionChanged: {
            updateHue(mouse, wheelArea, _.trackInnerRadius, _.trackOuterRadius)
        }
        onPressed: {
            _.initialHue = control.hue
            updateHue(mouse, wheelArea, _.trackInnerRadius, _.trackOuterRadius)
        }
    }
}
