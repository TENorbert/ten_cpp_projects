import Qt 4.7

Item {
    id: breadcrumb
    height: menuBreadcrumb.height

    property alias text: menuBreadcrumb.text
    property variant breadcrumbfont: ""
    property bool breadcrumbfontbold: true
    property int pointsize: 26
    property alias color: menuBreadcrumb.color
    //property real  xpos: menuBreadcrumb.x
    //property real  ypos: menuBreadcrumb.y
  
	
    Text {
        id: menuBreadcrumb
        width: parent.width
        anchors{ horizontalCenter:parent.center; top:parent.top; topMargin: 5 }
        x: 173
        y: 5
        text: ""
        color: "black" //"white"
        font { pixelSize: 26; }
        //elide: Text.ElideMiddle
        font.family: breadcrumbfont
        font.bold: breadcrumbfontbold
        //font.pointSize : pointsize
        
    }
}
