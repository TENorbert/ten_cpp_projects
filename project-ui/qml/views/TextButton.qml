import QtQuick 1.0

Rectangle {
    id: textButton

    property alias text: label.text
    property alias font: label.font

    width: 100; height: 60

    color: "lightsteelblue" //"#616365"
    radius: 10

    Text {
        id: label
        anchors.fill: parent
        font.pixelSize: 20
        font.bold: true
        horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
        color: "black" //"white"
        wrapMode: Text.Wrap
    }
}
