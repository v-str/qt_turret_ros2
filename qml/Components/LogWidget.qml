import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    property ListModel logModel: ListModel {}
    property int logCount: 0
    property color accentColor: SpaceMill.spaceSuccess

    function appendLog(msg, type) {
        logModel.append({ text: msg, type: type })
        logCount++
        if (logCount > 100) {
            logModel.remove(0)
            logCount--
        }
        logView.positionViewAtEnd()
    }

    Rectangle {
        anchors.fill: parent
        color: "transparent"
        radius: 5
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 8
        spacing: 4

        Label {
            text: "Лог"
            color: accentColor
            font.pixelSize: 13
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: SpaceMill.spaceElementAlpha
            border.width: 0.5
            border.color: SpaceMill.spaceBorder
            radius: 4
            clip: true

            ListView {
                id: logView
                anchors.fill: parent
                anchors.margins: 4
                model: logModel
                delegate: Text {
                    text: model.text
                    color: {
                        switch (model.type) {
                            case 1: return SpaceMill.spaceSuccess
                            case 2: return "red"
                            case 3: return SpaceMill.spaceTextMuted
                            default: return SpaceMill.spaceText
                        }
                    }
                    font.pixelSize: 10
                    bottomPadding: 2
                }
            }
        }
    }
}
