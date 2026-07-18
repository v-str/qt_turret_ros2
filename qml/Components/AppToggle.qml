import QtQuick

Item {
    id: root
    implicitWidth: 60
    implicitHeight: 30

    property string text: ""
    property bool checked: false
    property bool isEnabled: true
    property color activeColor: SpaceMill.spaceSuccess

    signal toggled(bool checked)

    Rectangle {
        id: track
        anchors.fill: parent
        radius: height / 2
        color: SpaceMill.spaceElementAlpha
        border.width: 1
        border.color: root.isEnabled
            ? (root.checked ? root.activeColor : SpaceMill.spaceTextMuted)
            : SpaceMill.spaceTextMuted
    }

    Rectangle {
        id: thumb
        width: parent.height - 6
        height: width
        radius: width / 2
        y: 3
        x: root.checked ? parent.width - width - 3 : 3
        color: root.isEnabled
            ? SpaceMill.spaceText
            : SpaceMill.spaceTextMuted

        Behavior on x {
            NumberAnimation { duration: 120; easing.type: Easing.InOutQuad }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (root.isEnabled) {
                root.checked = !root.checked
                root.toggled(root.checked)
            }
        }
    }
}
