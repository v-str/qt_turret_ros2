import QtQuick

Item {
    Image {
        id: cameraImage
        anchors.fill: parent
        source: "image://turret/feed"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        source: "qrc:/images/crosshair.png"
        anchors.centerIn: parent
        width: 60
        height: 60
        sourceSize.width: 60
        sourceSize.height: 60
        fillMode: Image.PreserveAspectFit
    }

    Timer {
        interval: 33
        running: true
        repeat: true
        onTriggered: cameraImage.source = "image://turret/feed?" + Date.now()
    }
}
