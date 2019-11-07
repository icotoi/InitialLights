import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import "../Constants"

Text {
    text: "All your lightes are now in one single place"

    property int size: ILStyle.TextSize.Large

    bottomPadding: 6
    lineHeight: 1.15
    wrapMode: Text.WordWrap
    font: size === ILStyle.TextSize.Large
          ? ILStyle.largeTitleTextFont
          : (size === ILStyle.TextSize.Medium ? ILStyle.mediumTitleTextFont : ILStyle.smallTitleTextFont)
    color: ILStyle.titleTextColor
}


/*##^##
Designer {
    D{i:0;height:25;width:320}
}
##^##*/
