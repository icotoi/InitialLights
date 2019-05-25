import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "Images"

Item {
    width: 400
    height: 400

    Image {
        id: image
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        source: "Images/pixabay_illumination-lights-bulbs-731494_1920.jpg"
    }
}
