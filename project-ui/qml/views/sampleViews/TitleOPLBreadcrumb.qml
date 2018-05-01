import Qt 4.7

Rectangle {
      id: titlebreadcrumb
      height: textTitlebreadcrumb.height

      property alias text: textTitlebreadcrumb.text
      property variant breadcrumbfont: ""
      property bool breadcrumbfontbold: false
      property int pointsize: 26
	
      Text {
        id: textTitlebreadcrumb
        width: parent.width
        anchors.horizontalCenter: parent.horizontalCenter
        text: ""
        color: "white"
        font { pixelSize: 20; }
        //elide: Text.ElideMiddle
        font.family: breadcrumbfont
        font.bold: breadcrumbfontbold
        font.pointSize : pointsize
        
     }
   }
