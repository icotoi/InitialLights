import QtQuick 2.0

Item {
    id: root
    width: 200
    height: 200

    property real wheelSize: width < height ? width : height

    // if false, show the canvas color wheel
    // if true, show the shader color wheel
    property bool useShader: false

    // use 1 to get something like when using the shader color wheel
    // use > 1 to get discrete color sectors
    // works only with the canvas color wheel
    property int canvasAngleStep: 4

    Canvas {
        visible: !useShader
        anchors.centerIn: parent
        width: wheelSize
        height: wheelSize
        // renderStrategy: Canvas.Threaded

        onPaint: {
            var ctx = getContext("2d");
            ctx.reset();

            var x = width / 2;
            var y = height / 2;
            var radius = width / 2;
            var counterClockwise = false;
            var angleStep = canvasAngleStep

            for(var angle=0; angle<=360; angle+=angleStep){
                var offsetAngle = Math.PI
                var startAngle = (angle - angleStep - 1) * Math.PI/180 + offsetAngle;
                var endAngle = angle * Math.PI/180 + offsetAngle;
                var a = 360 - angle
                ctx.beginPath();
                ctx.moveTo(x, y);
                ctx.arc(x, y, radius, startAngle, endAngle, counterClockwise);
                ctx.closePath();
                ctx.fillStyle = 'hsl('+a+', 100%, 50%)';
                ctx.fill();
            }
        }
    }

    Rectangle {
        visible: useShader
        width: wheelSize
        height: wheelSize
        anchors.centerIn: parent
        color: "transparent"

        ShaderEffect {
            id: shader
            anchors.fill: parent
            vertexShader: "
                uniform highp mat4 qt_Matrix;
                attribute highp vec4 qt_Vertex;
                attribute highp vec2 qt_MultiTexCoord0;
                varying highp vec2 coord;

                void main() {
                    coord = qt_MultiTexCoord0 - vec2(0.5, 0.5);
                    gl_Position = qt_Matrix * qt_Vertex;
            }"
            fragmentShader: "
                varying highp vec2 coord;

                vec3 hsv2rgb(in vec3 c){
                    vec4 k = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
                    vec3 p = abs(fract(c.xxx + k.xyz) * 6.0 - k.www);
                    return c.z * mix(k.xxx, clamp(p - k.xxx, 0.0, 1.0), c.y);
                }

                void main() {
                    const float PI = 3.14159265358979323846264;
                    float s = sqrt(coord.x * coord.x + coord.y * coord.y);

                    if( s > 0.5 ){
                        gl_FragColor = vec4(0, 0, 0, 0);
                        return;
                    }

                    float h = - atan( coord.y / coord.x );
                    s *= 2.0;

                    if( coord.x >= 0.0 ){
                        h += PI;
                    }

                    h = h / (2.0 * PI);
                    //vec3 hsl = vec3(h, s, 1.0);
                    vec3 hsl = vec3(h, 1.0, 1.0);
                    vec3 rgb = hsv2rgb(hsl);
                    gl_FragColor.rgb = rgb;
                    gl_FragColor.a = 1.0;
            }"
        }
    }
}
