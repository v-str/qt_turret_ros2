import QtQuick
import QtQuick.Layouts
import "Components"

Item {
    id: rootItem

    // фон — камера
    Image {
        id: cameraImage
        anchors.fill: parent
        source: "image://turret/feed"
        fillMode: Image.PreserveAspectFit
    }

    // виньетка-подложка поверх кадра
    Rectangle {
        anchors.fill: parent
        color: Qt.rgba(0.02, 0.04, 0.07, 0.35)
    }

    // обрамляющие угловые скобки экрана
    // прицел (не меняем)
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

    // зона прицеливания
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
        anchors.topMargin: 10
        text: "CTRL+0 — ОТКЛ. БОЕВОЙ РЕЖИМ\nCTRL+L — ЛАЗЕР"
        color: SpaceMill.err
        font.family: "Source Code Pro"
        font.pixelSize: 12
        font.letterSpacing: 1
        visible: combatToggle.checked
    }

    // -------- верхняя панель управления --------
    RowLayout {
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 12
        anchors.right: parent.right
        anchors.rightMargin: 12
        spacing: 10

        // левая стойка кнопок
        ColumnLayout {
            spacing: 6
            Layout.alignment: Qt.AlignTop

            AppBtn {
                id: manualBtn
                text: "Ручное управление"
                frameColor: combatToggle.checked ? SpaceMill.err : SpaceMill.accent
                textColor: combatToggle.checked ? SpaceMill.err : SpaceMill.accent
                Layout.preferredWidth: 210
                Layout.minimumWidth: 210
                Layout.maximumWidth: 210
                onClicked: turretWidget.sendCommand(0)
            }

            AppBtn {
                id: patrolBtn
                text: "Патрулирование"
                frameColor: combatToggle.checked ? SpaceMill.err : SpaceMill.accent
                textColor: combatToggle.checked ? SpaceMill.err : SpaceMill.accent
                Layout.preferredWidth: 210
                Layout.minimumWidth: 210
                Layout.maximumWidth: 210
            }

            AppBtn {
                id: calibrateBtn
                text: "Калибровка"
                frameColor: combatToggle.checked ? SpaceMill.err : SpaceMill.accent
                textColor: combatToggle.checked ? SpaceMill.err : SpaceMill.accent
                Layout.preferredWidth: 210
                Layout.minimumWidth: 210
                Layout.maximumWidth: 210
                onClicked: turretWidget.sendCommand(2)
            }
        }

        Item {
            Layout.fillWidth: true
        }

        // правый статусный модуль боевого режима
        Item {
            Layout.alignment: Qt.AlignRight | Qt.AlignTop
            Layout.preferredWidth: 200
            Layout.preferredHeight: combatToggle.checked ? 88 : 70

            Chamfer {
                anchors.fill: parent
                cut: 8
                fillColor: Qt.rgba(0.04, 0.07, 0.11, 0.66)
                borderColor: combatToggle.checked ? SpaceMill.err : SpaceMill.edgeBright
                borderWidth: 1
            }

            Column {
                anchors.fill: parent
                anchors.leftMargin: 12
                anchors.topMargin: 8
                spacing: 6

                AppLabel {
                    text: "Боевой режим"
                    header: true
                    color: combatToggle.checked ? SpaceMill.err : SpaceMill.textDim
                }

                AppToggle {
                    id: combatToggle
                    activeColor: combatToggle.checked ? SpaceMill.err : SpaceMill.ok
                    blocked: turretWidget ? turretWidget.combatBlocked : false
                    onBlockedClicked: turretWidget.logRequested(
                        "Перевод в боевой режим невозможен: " + turretWidget.combatBlockedReason, 2)
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
                    text: turretWidget ? (turretWidget.laserOn ? "Лазер активен" : "Лазер выключен") : ""
                    color: turretWidget && turretWidget.laserOn ? SpaceMill.err : SpaceMill.textDim
                    visible: combatToggle.checked
                }
            }
        }
    }

    // вспышка-рамка в боевом режиме
    Rectangle {
        id: flashRect
        anchors.fill: parent
        color: "transparent"
        border.color: SpaceMill.err
        border.width: 0
        radius: 2
        z: 999

        SequentialAnimation {
            id: flashAnim
            PropertyAnimation {
                target: flashRect
                property: "border.width"
                from: 0
                to: 8
                duration: 180
            }
            PropertyAnimation {
                target: flashRect
                property: "border.width"
                from: 8
                to: 0
                duration: 180
            }
        }
    }

    // нижний док: логи | наклон | температура | поворот
    Item {
        id: dockPanel
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: 186

        Chamfer {
            anchors.fill: parent
            cut: 8
            fillColor: Qt.rgba(0.04, 0.07, 0.11, 0.55)
            borderColor: SpaceMill.edgeBright
            borderWidth: 1
        }

        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 12
            anchors.rightMargin: 12
            anchors.topMargin: 10
            anchors.bottomMargin: 8
            spacing: 10

            LogWidget {
                id: logWidget
                Layout.fillWidth: true
                Layout.minimumWidth: 200
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignBottom
                accentColor: combatToggle.checked ? SpaceMill.err : SpaceMill.ok
            }

            // температура ЭВМ
            TemperatureWidget {
                Layout.preferredWidth: 150
                Layout.minimumWidth: 120
                Layout.preferredHeight: 162
                Layout.alignment: Qt.AlignBottom
                Layout.fillHeight: true
            }

            // шкала наклона
            Item {
                id: angleGroup
                Layout.preferredWidth: 150
                Layout.minimumWidth: 120
                Layout.preferredHeight: 162
                Layout.alignment: Qt.AlignBottom

                Image {
                    anchors.fill: parent
                    source: "qrc:/images/turret_no_bg_angle_plate.png"
                    fillMode: Image.PreserveAspectCrop
                }

                Image {
                    id: angleGunImage
                    anchors.fill: parent
                    source: "qrc:/images/turret_no_bg_angle_gun.png"
                    fillMode: Image.PreserveAspectCrop
                }
            }

            // турель по углу поворота
            Item {
                id: turretGroup
                Layout.preferredWidth: 160
                Layout.minimumWidth: 120
                Layout.preferredHeight: 162
                Layout.alignment: Qt.AlignBottom

                Image {
                    anchors.fill: parent
                    source: "qrc:/images/turret_no_bg_base.png"
                    fillMode: Image.PreserveAspectCrop
                    transform: Rotation {
                        origin.x: turretGroup.width / 2
                        origin.y: turretGroup.height / 2
                        angle: -90
                    }
                }

                Image {
                    anchors.fill: parent
                    source: "qrc:/images/turret_no_bg_gun_kontur.png"
                    fillMode: Image.PreserveAspectCrop
                    x: -5
                    transform: Rotation {
                        origin.x: turretGroup.width / 2
                        origin.y: turretGroup.height / 2
                        angle: -270
                    }
                }
            }
        }
    }

    Shortcut {
        id: exitShortcut
        sequence: "Ctrl+0"
        onActivated: {
            combatToggle.checked = !combatToggle.checked
        }
    }

    Shortcut {
        id: laserShortcut
        sequence: "Ctrl+L"
        onActivated: turretWidget.toggleLaser()
    }

    Connections {
        target: turretWidget
        function onLogRequested(msg, type) { logWidget.appendLog(msg, type) }
        function onCombatBlockedChanged() {
            if (turretWidget.combatBlocked)
                combatToggle.checked = false
        }
    }

    Timer {
        id: frameTimer
        interval: 33
        running: true
        repeat: true
        onTriggered: cameraImage.source = "image://turret/feed?" + Date.now()
    }
}