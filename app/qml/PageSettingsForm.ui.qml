import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "Images"
import "Controls"
import "Constants"

Item {
    property alias bluetoothScanButton: bluetoothScanButton
    ToolButton {
        id: bluetoothScanButton
        icon.source: "Images/material.io-sharp-bluetooth_searching-24px.svg"
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
