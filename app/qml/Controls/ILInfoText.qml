import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import "../Constants"

Text {
    text: qsTr("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nunc sed dui in nulla auctor volutpat vitae non sem. In hac.")

    enum Size {
        Normal,
        Small
    }
    property int size: ILInfoText.Size.Normal

    lineHeight: 1.1
    wrapMode: Text.WordWrap
    font: size === ILInfoText.Size.Normal ? ILStyle.normalInfoTextFont : ILStyle.smallInfoTextFont
    color: ILStyle.infoTextColor
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:0;width:320}
}
##^##*/
