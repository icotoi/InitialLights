import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.1

Page {
    id: page
    width: 400
    height: 600

    header: Label {
        text: qsTr("Main")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    ColumnLayout {
        id: column1
        anchors.fill: parent
        GridLayout {
            id: grid1
            columns: 4
            rows: 2

            columnSpacing: 15
            rowSpacing: 15

            Layout.fillHeight: true
            Layout.fillWidth: true

            ToggleButton {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            ToggleButton {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            ToggleButton {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            ToggleButton {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            ToggleButton {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            ToggleButton {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            ToggleButton {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            ToggleButton {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }

        GridLayout {
            columnSpacing: 15
            rowSpacing: 15
            columns: 1
            rows: 1

            Layout.fillHeight: true
            Layout.fillWidth: true

            Rectangle {
                id: rectangle
                height: 110
                Layout.fillWidth: true

                RoundButton {
                    width: 80
                    height: 80
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    Layout.fillWidth: false
                    Layout.fillHeight: false
                }
            }
        }

        GridLayout {
            id: grid2
            columns: 4
            rows: 2

            Layout.fillHeight: true
            Layout.fillWidth: true

            columnSpacing: 15
            rowSpacing: 15

            ToggleButton {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            ToggleButton {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            ToggleButton {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            ToggleButton {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            ToggleButton {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            ToggleButton {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            ToggleButton {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            ToggleButton {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }
}
