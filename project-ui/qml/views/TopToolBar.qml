/* Use For Bottom Tool Bar with 4 Button Images */
import Qt 4.7

Rectangle{
      id: toptoolbar
      color: "#0082c8"

      property string breadcrumbText: breadcrumb.text
      Item {
            id: itemcontainer
            anchors { fill: parent } //; margins: 10
      
            OPLBreadcrumb {
                id: breadcrumb
                anchors{
                       top: parent.top
                       topMargin: 5
                       horizontalCenter: parent.horizontalCenter
                       }
                width: parent.width
                breadcrumbfont :  brdcrumbfont
                breadcrumbfontbold : fontBold  
                text : ""
            }
      }
}
