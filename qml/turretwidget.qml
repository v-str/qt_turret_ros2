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
        source: combatToggle.checked
            ? "qrc:/images/crosshair.png"
            : "qrc:/images/crosshair_disabled.png"
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
            Layout.topMargin: 6
            Layout.leftMargin: 6
            spacing: 8

            Rectangle {
                width: parent.width
                height: parent.height
                radius: 6
                color: Qt.rgba(0.15, 0.15, 0.15, 0.25)
            }

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
                    id: combatToggle
                    Layout.alignment: Qt.AlignRight
                }
            }
        }

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

    }

    LogWidget {
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 6
        anchors.bottomMargin: 6
        width: 250
        height: 350
    }
}
