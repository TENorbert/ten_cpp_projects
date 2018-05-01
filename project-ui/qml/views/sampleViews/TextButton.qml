import QtQuick 1.0

Rectangle {
    id: textButton

    property alias text: label.text
    property alias font: label.font

    width: 100; height: 50

    color: "#616365"
    radius: 10

    Text {
        id: label
        anchors.fill: parent
        font.pixelSize: 20
        horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
        color: "white"
        wrapMode: Text.Wrap
    }
}
