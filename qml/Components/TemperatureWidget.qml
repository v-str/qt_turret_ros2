import QtQuick
import QtQuick.Layouts

// Панель температуры ЭВМ + тумблер охлаждения.
// C++ позже: сигналы температуры подключить к setTemperature(),
// охлаждение — читать coolingActive.
Item {
    id: tempWidget
    implicitWidth: 170
    implicitHeight: 162

    property real temperatureC: 0
    property bool coolingActive: false

    function setTemperature(v) {
        temperatureC = v
    }

    Chamfer {
        anchors.fill: parent
        cut: 8
        fillColor: Qt.rgba(0.04, 0.07, 0.11, 0.55)
        borderColor: SpaceMill.edgeBright
        borderWidth: 1
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 12
        spacing: 8

        AppLabel {
            text: "Температура\nмодуля"
            header: true
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
        }

        Text {
            text: (turretWidget ? turretWidget.temperature : tempWidget.temperatureC).toFixed(1) + " °C"
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            font.family: "Source Code Pro"
            font.pixelSize: 24
            font.weight: Font.Light
            color: SpaceMill.accent
        }

        AppLabel {
            text: "вкл. обдув"
            Layout.alignment: Qt.AlignHCenter
            color: tempWidget.coolingActive ? SpaceMill.ok : SpaceMill.textDim
        }

        AppToggle {
            id: coolingToggle
            Layout.alignment: Qt.AlignHCenter
            activeColor: SpaceMill.ok
            onToggled: function(checked) {
                tempWidget.coolingActive = checked
                turretWidget.logRequested(
                    checked ? "Охлаждение включено" : "Охлаждение выключено",
                    checked ? 1 : 0)
            }
        }
    }
}