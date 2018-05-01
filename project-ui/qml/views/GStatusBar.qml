import QtQuick 1.0

Item {
    id: statusBar
    anchors { top: parent.top; }
    width: parent.width; height: 26

    property int dateFormat: 0
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
            if(dateFormat==0)
            {
            	date.text = Qt.formatDate(datetime, "MM.dd.yyyy")
            }	
            else
            { 
           		date.text = Qt.formatDate(datetime, "dd.MM.yyyy")
           	}	 
        }
    }

    Text {
        id: time
        anchors.left: parent.left
        color: "white"
        font.pixelSize: 20
        visible: displayDateTime
        font.family : "helvetica"
		font.bold : false
    }

    Text {
        id: date
        anchors.right: parent.right
        color: "white"
        font.pixelSize: 20
        visible: displayDateTime
        font.family : "helvetica"
        font.bold : false

    }

    Text {
        id: title
        anchors.centerIn: parent
        color: "white"
        font.pixelSize: 20
        visible: displayDateTime
        font.family : "helvetica"
        font.bold : false

    }

    /* horizontal bar */
    Rectangle {
        width: parent.width; height: 2
        anchors.bottom: parent.bottom
        color: "#616365"
    }
}
