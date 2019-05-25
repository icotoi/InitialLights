import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "Controls"

Item {
    id: element
    width: 400
    height: 400
    property alias bottomGridLayout: bottomGridLayout
    property alias topGridLayout: topGridLayout

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent

        GridLayout {
            id: topGridLayout
            Layout.fillHeight: true
            Layout.bottomMargin: 20
            Layout.topMargin: 20
            Layout.rightMargin: 20
            Layout.leftMargin: 20
            Layout.fillWidth: true
            columns: 3
        }

        ILMainPowerButton {
            Layout.fillWidth: true

        }

        GridLayout {
            id: bottomGridLayout
            Layout.fillHeight: true
            Layout.bottomMargin: 20
            Layout.fillWidth: true
            Layout.rightMargin: 20
            columns: 3
            Layout.leftMargin: 20
            Layout.topMargin: 20
        }
    }
}
