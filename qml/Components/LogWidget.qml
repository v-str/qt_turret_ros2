import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    property ListModel logModel: ListModel {}
    property int logCount: 0
    property color accentColor: SpaceMill.ok

    function appendLog(msg, type) {
        logModel.append({ text: msg, type: type })
        logCount++
        if (logCount > 100) {
            logModel.remove(0)
            logCount--
        }
        logView.positionViewAtEnd()
    }

    // корпус со срезанными углами
    Chamfer {
        anchors.fill: parent
        cut: 8
        fillColor: Qt.rgba(0.04, 0.07, 0.11, 0.78)
        borderColor: SpaceMill.edgeBright
        borderWidth: 1
    }

    // заголовок
    Text {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: 14
        anchors.topMargin: 8
        text: "ЖУРНАЛ"
        color: accentColor
        font.family: "Source Code Pro"
        font.pixelSize: 10
        font.letterSpacing: 2
        font.capitalization: Font.AllUppercase
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.leftMargin: 14
        anchors.rightMargin: 8
        anchors.topMargin: 30
        anchors.bottomMargin: 6
        spacing: 2

        ListView {
            id: logView
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: logModel
            delegate: Text {
                text: model.text
                color: {
                    switch (model.type) {
                        case 1: return SpaceMill.ok
                        case 2: return SpaceMill.err
                        case 3: return SpaceMill.warn
                        default: return SpaceMill.text
                    }
                }
                font.family: "Source Code Pro"
                font.pixelSize: 10
                font.letterSpacing: 0.5
                bottomPadding: 3
                wrapMode: Text.Wrap
            }
        }
    }
}