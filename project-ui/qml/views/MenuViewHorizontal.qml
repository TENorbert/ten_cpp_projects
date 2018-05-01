import Qt 4.7

import com.ecolab.components 1.0

Rectangle 
{
    id: screen
    anchors.fill: parent
	width: 480
	height: 272
       
    property alias breadcrumb: breadcrumb.text
    property alias softKeyIconList: softkeys.softkeyIconList
    property alias btnIcon1: softkeys.btnIcon1
    property alias btnIcon2: softkeys.btnIcon2
    property alias btnIcon3: softkeys.btnIcon3
    property alias btnIcon4: softkeys.btnIcon4
    property alias menuModel : menu.model	
    property alias menuSpacing : menu.spacing
    property alias menuDelegate : menu.delegate
    property alias menuHighlight: menu.highlight
	property alias source: menuLoader.source
    property bool viewHighlight : true
    property int menuleftMargin : 10
	property variant qmlFile : ""
	property alias currentIndex: menu.currentIndex
	property alias menuLoaderItem : menuLoader.item
    
    property variant screenfont :  AquanomicsLM.GetPrimaryLangaugeFontName()
    property bool fontBold :  AquanomicsLM.GetPrimaryLangaugeFontBoldStatus() 
    
    
        function reloadFontProperties()
    {
        screenfont =  AquanomicsLM.GetPrimaryLangaugeFontName()
        fontBold =  AquanomicsLM.GetPrimaryLangaugeFontBoldStatus() 
    }

    signal goBack()
    Loader 
	{
        id: menuLoader
        anchors.fill: parent
        source: ""

        onSourceChanged: 
		{

            if (source == "") 
			{
                menuView.visible = true
                menuView.focus = true
            }
			else 
			{
                menuLoader.focus = true
            }
        }
        onLoaded: {

                   	menuView.visible = false;
                  } 
    }
    Connections 
	{
        target: menuLoader.item
        onGoBack: 
		{
            menuLoader.source = "";
            reloadFontProperties();
            menuView.visible = true
            menuView.focus = true
        }
    }

    Rectangle 
	{
        id: menuView
        anchors.fill: parent
        color: "#0082c8"

        Item 
		{
            id: container
            anchors { fill: parent; margins: 5; }

            OPLStatusBar 
			{
                id: statusBar
                anchors.top: parent.top
                dateFormat : systemcontext.unitOfMeasure
            }
			
            OPLBreadcrumb 
			{
                id: breadcrumb
		anchors { top: statusBar.bottom; margins: 5 }
		width: parent.width
                breadcrumbfont :  brdcrumbfont
                breadcrumbfontbold : fontBold  

            }

            Item 
			{
                id: main
		anchors { left: parent.left; right: parent.right; bottom: softkeys.top; }
		anchors.top: (breadcrumb.text == "" ? statusBar.bottom : breadcrumb.bottom)
                anchors.topMargin: (breadcrumb.text == "" ? 10 : 5)
                anchors.bottomMargin: (breadcrumb.text == "" ? 10 : 9)

                width: parent.width

                /* The menu */
                ListView 
				{
                    id: menu
                    anchors { fill: parent; }
                    anchors.leftMargin : menuleftMargin
					//anchors { top: parent.top;  bottom: parent.bottom}
					//anchors.left : parent.left   ; 
					//anchors.centerIn : parent
					orientation: ListView.Horizontal
                    delegate: menuDelegate
                    highlight: menuHighlight
                    spacing: 35
                    clip: true
                    //width : (57+25)*3
                    Component.onCompleted: {
                    	positionViewAtIndex(currentIndex, ListView.Contain)
                    }
			    }


                Text {
                    id: errorText
                    anchors.centerIn: parent
                    text: "No list elements!"
                    color: "white"
                    font.pixelSize: 20
                    visible: menu.count == 0
                }

                Component 
				{
                    id: menuDelegate

                    Item 
					{
                        id: wrapper
                        width: 115; 
                        Column 
						{
						    anchors.fill: parent
							spacing : 5
							
							Image 
							{	
 							    id: imageSymbol 
								anchors.horizontalCenter: parent.horizontalCenter
								source: symbol
							}
							Text 
							{
								id: menuText
								font.pixelSize: 20
								anchors.horizontalCenter: parent.horizontalCenter
								text: name
								color: "white"
                                font.family : "helvetica"
                                font.bold : false
							}
						}
						

                        Keys.onReturnPressed: 
						{
                            if(qmlFile)
							{
							menuLoader.source = "../" + qmlFile
                            if (qmlFile == "Video.qml")
                                menuLoader.item.videoSource = videoDir + videoSource
							}	
                            event.accepted = true
                        }
                    }
                }

                Component 
				{
                    id: menuHighlight

                    Rectangle 
					{
                        color: "#616365"
                        radius: 5
                        width: menu.currentItem.width; height: menu.height
                        visible : viewHighlight 
                    }
                }
            }  
            SoftkeysWithIcons {
                id: softkeys
                anchors.bottom: parent.bottom

                softkeyIconList: ["qrc:/images/back-icon.png", "", "", "qrc:/images/help-icon.png"]
            }
        }

        focus: true
   
        Keys.forwardTo: [parent, menu]
        Keys.onPressed: 
		{
            /* disable auto repeat */
            if (!event.isAutoRepeat) 
			{
                switch (event.key) 
				{
                    case Qt.Key_Up:
                        break;
                    case Qt.Key_Right:
                        break;
                    case Qt.Key_Down:
                        break;
                    case Qt.Key_Left:
                        break;
                    case Qt.Key_F1:
						screen.goBack()
                        break;
                    case Qt.Key_F2:
					     break;
                    case Qt.Key_F3:
                        break;
                    case Qt.Key_F4:
                        {
                            screen.source ="../Help.qml"
                            event.accepted = true
                        }
						//menuLoader.source = "../Help.qml"
                        break;
                }
            }
			event.accepted = true
        }
    }
}
