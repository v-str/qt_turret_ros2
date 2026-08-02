import QtQuick
import QtQuick.Controls

Label {
    font.family: "Source Code Pro"
    font.letterSpacing: 2
    font.capitalization: Font.AllUppercase
    font.pixelSize: 11

    // header=true — приглушённый заголовок, иначе — яркое значение
    property bool header: false
    font.weight: header ? Font.Light : Font.Medium
    color: header ? SpaceMill.textDim : SpaceMill.text
}