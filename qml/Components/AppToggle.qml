import QtQuick

Item {
    id: toggleRoot
    implicitWidth: 60
    implicitHeight: 30

    property string text: ""
    property bool checked: false
    property bool isEnabled: true
    property color activeColor: SpaceMill.spaceSuccess
    property bool blocked: false

    signal toggled(bool checked)
    signal blockedClicked()

    Rectangle {
        id: track
        anchors.fill: parent
        radius: height / 2
        color: SpaceMill.spaceElementAlpha
        border.width: 1
        border.color: toggleRoot.isEnabled
            ? (toggleRoot.checked ? toggleRoot.activeColor : SpaceMill.spaceTextMuted)
            : SpaceMill.spaceTextMuted
    }

    Rectangle {
        id: thumb
        width: parent.height - 6
        height: width
        radius: width / 2
        y: 3
        x: toggleRoot.checked ? parent.width - width - 3 : 3
        color: toggleRoot.isEnabled
            ? SpaceMill.spaceText
            : SpaceMill.spaceTextMuted

        Behavior on x {
            NumberAnimation { duration: 120; easing.type: Easing.InOutQuad }
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
