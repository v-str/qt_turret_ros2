import QtQuick
import QtQuick.Controls

Button {
    id: control

    property color frameColor: SpaceMill.spaceSuccess
    property color textColor: SpaceMill.spaceSuccess
    property int clickDelay: 280

    signal delayedClick()

    Timer {
        id: clickTimer
        interval: control.clickDelay
        repeat: false
        onTriggered: control.delayedClick()
    }

    onClicked: clickTimer.restart()

    leftPadding: 12
    rightPadding: 12
    topPadding: 8
    bottomPadding: 8

    transform: Translate { id: pressTransform }

    onPressedChanged: {
        if (pressed) {
            releaseSeq.stop()
            waveRect.x = -waveRect.width
            pressTo.start()
        } else {
            pressTo.stop()
            releaseSeq.start()
        }
    }

    PropertyAnimation {
        id: pressTo
        target: pressTransform
        properties: "x,y"
        to: 2
        duration: 60
    }

    SequentialAnimation {
        id: releaseSeq
        PropertyAnimation {
            target: pressTransform
            properties: "x,y"
            to: 0
            duration: 60
        }
        PropertyAnimation {
            target: waveRect
            property: "x"
            from: -waveRect.width
            to: waveRect.parent.width
            duration: 150
        }
    }

    background: Rectangle {
        id: bg
        radius: 5
        color: "transparent"
        border.width: 0.5
        border.color: control.enabled ? control.frameColor : SpaceMill.spaceTextMuted
        clip: true

        Rectangle {
            id: waveRect
            width: parent.width * 0.4
            height: parent.height
            color: Qt.rgba(1, 1, 1, 0.12)
            x: -width
        }
    }

    contentItem: Text {
        text: control.text
        font: control.font
        color: control.enabled ? control.textColor : SpaceMill.spaceTextMuted
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}
