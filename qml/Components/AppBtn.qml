import QtQuick
import QtQuick.Controls

Button {
    id: control

    property color frameColor: SpaceMill.accent
    property color textColor: SpaceMill.accent
    property int clickDelay: 280

    signal delayedClick()

    Timer {
        id: clickTimer
        interval: control.clickDelay
        repeat: false
        onTriggered: control.delayedClick()
    }

    onClicked: clickTimer.restart()

    implicitHeight: 34
    leftPadding: 14
    rightPadding: 14
    topPadding: 6
    bottomPadding: 6

    transform: Translate { id: pressTransform }

    onPressedChanged: {
        if (pressed)
            pressTo.start()
        else
            pressTo.stop()
    }

    PropertyAnimation {
        id: pressTo
        target: pressTransform
        properties: "x,y"
        to: 1
        easing.type: Easing.OutQuad
        duration: 60
    }

    background: Chamfer {
        id: shape
        anchors.fill: parent
        cut: 8
        fillColor: control.enabled && control.hovered
            ? Qt.rgba(control.frameColor.r, control.frameColor.g,
                      control.frameColor.b, 0.14)
            : Qt.rgba(0.04, 0.07, 0.11, 0.72)
        borderColor: control.enabled
            ? (control.hovered ? control.frameColor : SpaceMill.edgeBright)
            : SpaceMill.textDim
        borderWidth: 1
    }

    contentItem: Text {
        text: control.text
        font.family: "Source Code Pro"
        font.pixelSize: 12
        font.letterSpacing: 1
        font.capitalization: Font.AllUppercase
        color: control.enabled ? control.textColor : SpaceMill.textDim
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }
}