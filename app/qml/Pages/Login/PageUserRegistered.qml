import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../../Controls"

Page {
    id: page
    signal done()

    ILBillboardItem {
        image: "../../Images/background-onboarding-3.jpg"
        title: "Congratulations! Your account was created!"
        message: "You can now use Initial Lights, don’t forget to confirm your email address, you will need this to unlock more features."
        textHorizontalMargin: 20
    }

    ILButton {
        id: nextButton
        text: qsTr("Continue")
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 36
        highlighted: true
        Layout.fillWidth: true
        onClicked: done()
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:640;width:360}
}
##^##*/
