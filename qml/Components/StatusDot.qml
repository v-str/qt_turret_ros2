import QtQuick

Rectangle {
    property bool active: false
    property color activeColor: SpaceMill.spaceSuccess
    property color inactiveColor: SpaceMill.spaceTextMuted

    width: 12
    height: 12
    radius: width / 2
    color: active ? activeColor : inactiveColor
}
