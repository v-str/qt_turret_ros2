import QtQuick
import QtQuick.Shapes

// Скошенный под 45° многоугольник (тактическая панель).
Item {
    id: cham
    antialiasing: true

    property color fillColor: "transparent"
    property color borderColor: SpaceMill.edgeBright
    property int borderWidth: 1
    property real cut: 8

    Shape {
        anchors.fill: parent

        ShapePath {
            fillColor: cham.fillColor
            strokeColor: cham.borderColor
            strokeWidth: cham.borderWidth
            startX: cham.cut
            startY: 0

            PathLine { x: cham.width - cham.cut; y: 0 }
            PathLine { x: cham.width; y: cham.cut }
            PathLine { x: cham.width; y: cham.height - cham.cut }
            PathLine { x: cham.width - cham.cut; y: cham.height }
            PathLine { x: cham.cut; y: cham.height }
            PathLine { x: 0; y: cham.height - cham.cut }
            PathLine { x: 0; y: cham.cut }
            PathLine { x: cham.cut; y: 0 }
        }
    }
}