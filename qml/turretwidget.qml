import QtQuick
import QtQuick.Layouts
import "Components"

Item {
    id: rootItem

    Image {
        id: cameraImage
        anchors.fill: parent
        source: "image://turret/feed"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: crosshairImg
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

    MouseArea {
        id: aimArea
        anchors.fill: parent
        enabled: combatToggle.checked
        hoverEnabled: combatToggle.checked
        cursorShape: combatToggle.checked ? Qt.BlankCursor : Qt.ArrowCursor
        onPositionChanged: function(mouse) {
            var cx = width / 2
            var cy = height / 2
            var dx = (mouse.x - cx) / cx
            var dy = (mouse.y - cy) / cy
            if (Math.abs(mouse.x - cx) > 1 || Math.abs(mouse.y - cy) > 1) {
                turretWidget.sendAimDelta(dx, dy)
                turretWidget.warpMouse(cx, cy)
            }
        }
    }

    Text {
        id: exitHint
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 8
        text: "Ctrl+0 — откл. боевой режим\nCtrl+L — вкл. целеуказатель"
        color: "red"
        font.pixelSize: 14
        visible: combatToggle.checked
    }

    ColumnLayout {
        id: mainLayout
        anchors.fill: parent
        spacing: 0

        RowLayout {
            id: topBar
            Layout.fillWidth: true
            Layout.topMargin: 6
            Layout.leftMargin: 10
            spacing: 8

            Rectangle {
                id: topBarBg
                width: parent.width
                height: parent.height
                radius: 6
                color: Qt.rgba(0.15, 0.15, 0.15, 0.25)
            }

            ColumnLayout {
                id: btnColumn
                Layout.alignment: Qt.AlignTop
                spacing: 4

                Rectangle {
                    width: parent.width
                    height: parent.height
                    color: SpaceMill.spaceElementAlpha
                    radius: 5
                }

                AppBtn {
                    id: manualBtn
                    text: "Ручное управление"
                    font.pixelSize: 13
                    Layout.preferredWidth: 150
                    Layout.minimumWidth: 150
                    Layout.maximumWidth: 150
                    frameColor: combatToggle.checked ? "red" : SpaceMill.spaceSuccess
                    textColor: combatToggle.checked ? "red" : SpaceMill.spaceSuccess
                    Component.onCompleted: background.color = SpaceMill.spaceElementAlpha
                    onClicked: turretWidget.sendCommand(0)
                }

                AppBtn {
                    id: patrolBtn
                    text: "Патрулирование"
                    font.pixelSize: 13
                    Layout.preferredWidth: 150
                    Layout.minimumWidth: 150
                    Layout.maximumWidth: 150
                    frameColor: combatToggle.checked ? "red" : SpaceMill.spaceSuccess
                    textColor: combatToggle.checked ? "red" : SpaceMill.spaceSuccess
                    Component.onCompleted: background.color = SpaceMill.spaceElementAlpha
                }

                AppBtn {
                    id: centerBtn
                    text: "Центрирование"
                    font.pixelSize: 13
                    Layout.preferredWidth: 150
                    Layout.minimumWidth: 150
                    Layout.maximumWidth: 150
                    frameColor: combatToggle.checked ? "red" : SpaceMill.spaceSuccess
                    textColor: combatToggle.checked ? "red" : SpaceMill.spaceSuccess
                    Component.onCompleted: background.color = SpaceMill.spaceElementAlpha
                    onClicked: turretWidget.sendCommand(2)
                }
            }

            Item {
                id: topBarSpacer
                Layout.fillWidth: true
            }

            ColumnLayout {
                id: toggleColumn
                Layout.alignment: Qt.AlignRight | Qt.AlignTop
                Layout.rightMargin: 6
                spacing: 2

                AppLabel {
                    id: combatLabel
                    text: "Боевой режим"
                    font.pixelSize: 13
                    color: combatToggle.checked ? "red" : SpaceMill.spaceSuccess
                    horizontalAlignment: Text.AlignRight
                    Layout.fillWidth: true
                }

                AppToggle {
                    id: combatToggle
                    Layout.alignment: Qt.AlignRight
                    activeColor: combatToggle.checked ? "red" : SpaceMill.spaceSuccess
                    onCheckedChanged: {
                        if (checked) {
                            flashAnim.start()
                        } else {
                            flashAnim.stop()
                            flashRect.border.width = 0
                            if (turretWidget.laserOn)
                                turretWidget.toggleLaser()
                        }
                    }
                }

                AppLabel {
                    id: laserLabel
                    text: turretWidget ? (turretWidget.laserOn ? "Лазер включён" : "Лазер выключен") : ""
                    font.pixelSize: 10
                    color: turretWidget && turretWidget.laserOn ? "red" : SpaceMill.spaceTextMuted
                    horizontalAlignment: Text.AlignRight
                    Layout.fillWidth: true
                    visible: combatToggle.checked
                }
            }
        }

        Item {
            id: mainSpacer
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    Rectangle {
        id: flashRect
        anchors.fill: parent
        color: "transparent"
        border.color: "red"
        border.width: 0
        radius: 4
        z: 999

        SequentialAnimation {
            id: flashAnim
            PropertyAnimation {
                target: flashRect
                property: "border.width"
                from: 0
                to: 6
                duration: 180
            }
            PropertyAnimation {
                target: flashRect
                property: "border.width"
                from: 6
                to: 0
                duration: 180
            }
        }
    }

    LogWidget {
        id: logWidget
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 10
        anchors.bottomMargin: 1
        width: 380
        height: 100
        accentColor: combatToggle.checked ? "red" : SpaceMill.spaceSuccess
        z: 1000
    }

    Shortcut {
        id: exitShortcut
        sequence: "Ctrl+0"
        enabled: combatToggle.checked
        onActivated: {
            combatToggle.checked = false
        }
    }

    Shortcut {
        id: laserShortcut
        sequence: "Ctrl+L"
        onActivated: turretWidget.toggleLaser()
    }

    Connections {
        target: turretWidget
        function onLogRequested(msg) { logWidget.appendLog(msg) }
    }

    Timer {
        id: frameTimer
        interval: 33
        running: true
        repeat: true
        onTriggered: cameraImage.source = "image://turret/feed?" + Date.now()
    }
}
