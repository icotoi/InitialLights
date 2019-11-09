import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import "../Constants"

Text {
    text: "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nunc sed dui in nulla auctor volutpat vitae non sem. In hac."

    property int size: ILStyle.TextSize.Large

    lineHeight: 1.1
    wrapMode: Text.WordWrap
    font: size === ILStyle.TextSize.Large
          ? ILStyle.largeInfoTextFont
          : (size === ILStyle.TextSize.Medium ? ILStyle.mediumInfoTextFont : ILStyle.smallInfoTextFont)
    color: ILStyle.infoTextColor
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:0;width:320}
}
##^##*/
