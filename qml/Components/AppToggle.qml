import QtQuick

Item {
    id: toggleRoot
    implicitWidth: 64
    implicitHeight: 28

    property string text: ""
    property bool checked: false
    property bool isEnabled: true
    property color activeColor: SpaceMill.ok
    property bool blocked: false

    signal toggled(bool checked)
    signal blockedClicked()

    // трек
    Rectangle {
        id: track
        anchors.fill: parent
        radius: 2
        color: toggleRoot.isEnabled
            ? (toggleRoot.checked
                ? Qt.rgba(activeColor.r, activeColor.g, activeColor.b, 0.18)
                : Qt.rgba(0.04, 0.07, 0.11, 0.72))
            : SpaceMill.textDim
        border.width: 1
        border.color: toggleRoot.isEnabled
            ? (toggleRoot.checked ? toggleRoot.activeColor : SpaceMill.edgeBright)
            : SpaceMill.textDim

        // свечение включённого состояния
        Rectangle {
            anchors.fill: parent
            visible: toggleRoot.isEnabled && toggleRoot.checked
            radius: 2
            color: "transparent"
            border.width: 2
            border.color: toggleRoot.activeColor
            opacity: 0.25

            SequentialAnimation on opacity {
                running: toggleRoot.checked
                loops: Animation.Infinite
                NumberAnimation { to: 0.55; duration: 900; easing.type: Easing.InOutSine }
                NumberAnimation { to: 0.25; duration: 900; easing.type: Easing.InOutSine }
            }
        }

        // сегменты-маркировка "OFF/ON"
        Row {
            anchors.centerIn: parent
            spacing: track.width * 0.32
            Text {
                text: "ON"
                color: toggleRoot.checked ? toggleRoot.activeColor : SpaceMill.textDim
                font.family: "Source Code Pro"
                font.pixelSize: 9
                font.letterSpacing: 1
                font.capitalization: Font.AllUppercase
            }
            Text {
                text: "ВКЛ"
                color: !toggleRoot.checked ? SpaceMill.text : SpaceMill.textDim
                font.family: "Source Code Pro"
                font.pixelSize: 9
                font.letterSpacing: 1
                font.capitalization: Font.AllUppercase
            }
        }
    }

    // слайдер
    Rectangle {
        id: thumb
        width: parent.height - 8
        height: width
        radius: 2
        y: 4
        x: toggleRoot.checked ? parent.width - width - 4 : 4
        color: toggleRoot.isEnabled ? SpaceMill.text : SpaceMill.textDim

        Behavior on x {
            NumberAnimation { duration: 130; easing.type: Easing.InOutQuad }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (toggleRoot.isEnabled) {
                if (toggleRoot.blocked) {
                    toggleRoot.blockedClicked()
                } else {
                    toggleRoot.checked = !toggleRoot.checked
                    toggleRoot.toggled(toggleRoot.checked)
                }
            }
        }
    }
}