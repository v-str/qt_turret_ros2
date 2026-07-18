import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    property ListModel logModel: ListModel {}
    property int logCount: 0

    function appendLog(msg) {
        logModel.append({ text: msg })
        logCount++
        if (logCount > 100) {
            logModel.remove(0)
            logCount--
        }
        logView.positionViewAtEnd()
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 4

        Label {
            text: "Журнал операций"
            color: SpaceMill.spaceTextMuted
            font.pixelSize: 11
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "transparent"
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
                    color: SpaceMill.spaceText
                    font.pixelSize: 10
                    bottomPadding: 2
                }
            }
        }
    }
}
