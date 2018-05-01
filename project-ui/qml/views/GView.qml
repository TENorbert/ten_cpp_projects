import QtQuick 1.0
import com.ecolab.components 1.0
Rectangle {
    id: screen
    width: 480
    height: 272
    color: "lightsteelblue"

    default property alias content: stack.children
    property alias backGroundColor: view.color

    property alias breadcrumb: breadcrumb.text
    property alias numberedbreadcrumb: numberedbreadcrumb.text
    property alias headertext: headerinfo.text
    property alias footertext: footerinfo.text
    
    property alias softKeyIconList: softkeys.softkeyIconList
    property alias btnIcon1: softkeys.btnIcon1
    property alias btnIcon2: softkeys.btnIcon2
    property alias btnIcon3: softkeys.btnIcon3
    property alias btnIcon4: softkeys.btnIcon4
    property alias viewColor: view.color
    property alias source: viewLoader.source
    property alias item: viewLoader.item

    property int stackMargin: 5

    property bool isTMScreen : true
    property bool setEntireScreenSameFont : true
    property variant overridebrdcrumbfont: ""
    property variant overrideheaderinfofont: ""
    property variant overridenumberedbreadcrumbfont: ""
    property variant overridefooterinfofont: ""
    //property variant screenfont: (isTMScreen==true)? AquanomicsLM.GetTMLangaugeFontName() : AquanomicsLM.GetPrimaryLangaugeFontName()
    property variant screenfont: "helvetica"
    property variant headerinfofont : (setEntireScreenSameFont==true) ? screenfont: overrideheaderinfofont
    property variant brdcrumbfont : (setEntireScreenSameFont==true) ?  screenfont : ""
    property variant numberedbreadcrumbfont : (setEntireScreenSameFont==true) ? screenfont: overridenumberedbreadcrumbfont
    property variant footerinfofont : (setEntireScreenSameFont==true) ? screenfont: overridefooterinfofont
    //property bool fontBold : (isTMScreen==true)? AquanomicsLM.GetTMLangaugeFontBoldStatus() : false
    property bool fontBold : false

    function reloadFontProperties()
    {
        //console.log("************Inside reloadFontProperties*******");
        
        //screen.screenfont = (isTMScreen==true)? AquanomicsLM.GetTMLangaugeFontName() : AquanomicsLM.GetTMLangaugeFontName()
        screen.screenfont = "helvetica"
        headerinfofont = (setEntireScreenSameFont==true) ? screenfont: overrideheaderinfofont
        numberedbreadcrumbfont = (setEntireScreenSameFont==true) ? screenfont: overridenumberedbreadcrumbfont
        footerinfofont = (setEntireScreenSameFont==true) ? screenfont: overridefooterinfofont
       
        //screen.fontBold = (isTMScreen==true)? AquanomicsLM.GetTMLangaugeFontBoldStatus() : false
        screen.fontBold = false
        brdcrumbfont =  (setEntireScreenSameFont==true) ? screenfont: overridebrdcrumbfont
        //console.log("************DONE*******");
        
    }

    signal goBack()

    Loader {
        id: viewLoader
        anchors.fill: parent
        source: ""

        onSourceChanged: {
            if (source == "") {
                view.visible = true
                view.focus = true
            } else {
                viewLoader.focus = true
            }
        }
        onLoaded: view.visible = false;
    }

    Connections {
        target: viewLoader.item
        onGoBack: {
            viewLoader.source = "";
            reloadFontProperties()
            view.visible = true
            view.focus = true
        }
    }

    Rectangle {
        id: view
        anchors.fill: parent
        color: "lightsteelblue" // "#0082c8"
        radius: 10

        Item {
            id: container
            anchors { fill: parent; margins: 10; }

            GBreadcrumb {
                id: breadcrumb
                anchors { top: parent.top; margins: 5 }
                width: (numberedbreadcrumb.text == "" ? parent.width: (parent.width - numberedbreadcrumb.width-20))
                breadcrumbfont :  brdcrumbfont
                breadcrumbfontbold : fontBold  
            }
            
          Text {
                id: numberedbreadcrumb
                anchors.top: parent.top
				anchors.right: parent.right; 
				anchors.rightMargin: 10;
				anchors.topMargin: 5;
                width: text.width
				color: "white"
				font { pixelSize: 20; }
				elide: Text.ElideLeft
                font.family : numberedbreadcrumbfont
                font.bold : fontBold
            }
            
            Text {
                id: headerinfo
                anchors.top: breadcrumb.bottom
                anchors.topMargin : 2
                width: text.width
                color: "yellow"
				font { pixelSize: 16; }
				elide: Text.ElideLeft
                font.family : headerinfofont
                font.bold : fontBold
                
            }
            

            Item {
                id: stack
                anchors { top: (headerinfo.text == "" ? breadcrumb.bottom : headerinfo.bottom); left: parent.left; bottom: (footerinfo.text == "" ? softkeys.top : footerinfo.top); right: parent.right; margins: screen.stackMargin; }
            }
            
           Text {
                id: footerinfo
                anchors.bottom: softkeys.top
                width: text.width
                anchors.bottomMargin: 5
                color: "yellow"
				font { pixelSize: 16; }
				elide: Text.ElideLeft
                font.family : footerinfofont
                font.bold : fontBold
                
            }
            
            

            GSoftkeysWithIcons {
                id: softkeys
                x: 5//10 
                y: 203//230//213
                //anchors{
                //rightMargin: 10
                //leftMargin: 5
                //bottomMargin: 15
                //}

                softkeyIconList: ["", "", "", ""]
            }
        }

        focus: true
        Keys.forwardTo: parent
        Keys.onPressed: {
            /* disable auto repeat */
            if (!event.isAutoRepeat) {
                switch (event.key) {
                    case Qt.Key_Up:
                        break;
                    case Qt.Key_Right:
                        break;
                    case Qt.Key_Down:
                        break;
                    case Qt.Key_Left:
                        break;
                    case Qt.Key_F1:
                        break;
                    case Qt.Key_F2:
                        break;
                    case Qt.Key_F3:
                        break;
                    case Qt.Key_F4:
                    {
                        screen.source ="../Help.qml"
                        event.accepted = true
                    }break;
                }
            }

            event.accepted = true
        }
    }
}
