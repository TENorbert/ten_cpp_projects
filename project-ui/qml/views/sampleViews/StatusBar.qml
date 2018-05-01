import QtQuick 1.0

Item {
    id: statusBar
    anchors { top: parent.top; }
    width: parent.width; height: 26

    property bool displayDateTime: true
    property alias titleText: title.text

    // timer to update the data and time every second
    Timer {
        id: systemTime
        interval: 1000; running: true; repeat: true
        triggeredOnStart: true
        onTriggered: {
            var datetime = new Date()
            time.text = Qt.formatTime(datetime, "hh:mm:ss ap")
            date.text = Qt.formatDate(datetime, "MM.dd.yyyy")
        }
    }

    Text {
        id: time
        anchors.left: parent.left
        color: "white"
        font.pixelSize: 20
        visible: displayDateTime
    }

    Text {
        id: date
        anchors.right: parent.right
        color: "white"
        font.pixelSize: 20
        visible: displayDateTime
    }

    Text {
        id: title
        anchors.centerIn: parent
        color: "white"
        font.pixelSize: 20
        visible: displayDateTime
    }

    /* horizontal bar */
    Rectangle {
        width: parent.width; height: 2
        anchors.bottom: parent.bottom
        color: "#616365"
    }
}
