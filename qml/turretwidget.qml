import QtQuick
import QtQuick.Layouts
import "Components"

Item {
    Image {
        id: cameraImage
        anchors.fill: parent
        source: "image://turret/feed"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        source: "qrc:/images/crosshair.png"
        anchors.centerIn: parent
        width: 60
        height: 60
        sourceSize.width: 60
        sourceSize.height: 60
        fillMode: Image.PreserveAspectFit
    }

    Timer {
        interval: 33
        running: true
        repeat: true
        onTriggered: cameraImage.source = "image://turret/feed?" + Date.now()
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 56
            Layout.topMargin: 6
            Layout.leftMargin: 6
            spacing: 8

            ColumnLayout {
                Layout.alignment: Qt.AlignTop
                spacing: 4

                AppBtn {
                    text: "Ручное управление"
                    font.pixelSize: 13
                    Layout.preferredWidth: 140
                    Layout.minimumWidth: 140
                    Layout.maximumWidth: 140
                }

                AppBtn {
                    text: "Патрулирование"
                    font.pixelSize: 13
                    Layout.preferredWidth: 140
                    Layout.minimumWidth: 140
                    Layout.maximumWidth: 140
                }
            }

            Item {
                Layout.fillWidth: true
            }

            ColumnLayout {
                Layout.alignment: Qt.AlignRight | Qt.AlignTop
                Layout.rightMargin: 6
                spacing: 2

                AppLabel {
                    text: "Боевой режим"
                    font.pixelSize: 10
                    color: SpaceMill.spaceTextMuted
                    horizontalAlignment: Text.AlignRight
                }

                AppToggle {
                    Layout.alignment: Qt.AlignRight
                }
            }
        }

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        LogWidget {
            Layout.fillWidth: true
            Layout.preferredHeight: 100
            Layout.leftMargin: 6
            Layout.rightMargin: 6
            Layout.bottomMargin: 6
        }
    }
}
