import Qt 4.7

import com.ecolab.components 1.0

Rectangle 
{
    id: screen
    anchors.fill: parent
	width: 480
	height: 272

    property alias customerName: breadcrumb.text
	
    property alias softKeyIconList: softkeys.softkeyIconList
    property alias btnIcon1: softkeys.btnIcon1
    property alias btnIcon2: softkeys.btnIcon2
    property alias btnIcon3: softkeys.btnIcon3
    property alias btnIcon4: softkeys.btnIcon4

    property alias menuModel : menu.model	
    property alias menucount : menu.count
    property alias menuDelegate: menu.delegate
    property alias menuHighlight: menu.highlight
	property alias source: menuinfoLoader.source
	property alias statusImage: infoimage.source
	property alias statusImagewidth: infoimage.width
	property alias currentIndex: menu.currentIndex
	property alias headertext: headerBar.children
	
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
        id: menuinfoLoader
        anchors.fill: parent
        source: ""
        onSourceChanged: {
		                    
		                   menuinfoLoader.focus = true;
						  
						 } 
						 
        onLoaded: {

					 menuView.visible = false;
				  }	 
    }
    Connections 
	{
        target: menuinfoLoader.item
        onGoBack: 
		{
            menuinfoLoader.source = "";
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

			Image
			{
			  	id: infoimage
               	anchors { right: parent.right; rightMargin: 5; }
				source: ""
			}
            OPLBreadcrumb 
			{
                          id: breadcrumb
                          anchors.horizontalCenter:  parent.horizontalCenter
		          //anchors { left : parent.left; }
		          anchors.topMargin:10
                          width: parent.width
                          breadcrumbfont :  screenfont
                          breadcrumbfontbold : fontBold  

            }
            
			 Rectangle 
			{   
			    id: headerBar
				color: "red"
                radius: 5
				anchors.top: infoimage.bottom
				anchors.topMargin: 5
				anchors.bottomMargin: 5
				width: parent.width                      
				height: 10+ children.height
                	    Item {
				id: headerText
			     Text
				{
			          id: headerText1
                                  font.pixelSize: 20
                                  anchors.verticalCenter: parent.verticalCenter
//				  width: 100
//			 	  clip: true
				  color: "red"
                                  font.family : screenfont
                                  font.bold : fontBold
			     } 
		           }
		        } 
		    
				
            Item {
                id: main
	        anchors { left: parent.left; right: parent.right; bottom: softkeys.top; }
		anchors.top: headerBar.bottom
                anchors.topMargin: 20 
                anchors.bottomMargin: 0

                width: parent.width

      /* The menu */
               
          ListView 
                 {
                    id: menu
		  
                    anchors { fill: parent; }
                    delegate: menuDelegate
                 
                    highlight: menuHighlight  
                   // highlightFollowsCurrentItem : false //highlight across item controled by delegate on listView
                    spacing: 2
                    clip: true
					
                }
            Component 
                   {
                    id: menuDelegate

                    Item 
		        {
                        id: wrapper
			width: menuText.width; height: menuText.height + 10
                        x: 10
                        
                        Text 
			   {
                            id: menuText
                            font.pixelSize: 20
                            anchors.verticalCenter: parent.verticalCenter
                            text: name
			    
                            /*width: 100
			    clip: true*/
			    color: "white"
                            
                            font.family : screenfont
                            font.bold : fontBold
                        }
                            Keys.onReturnPressed: 
						{
                            event.accepted = true
                        }
                   }
          }

          /* Highlight component?*/
          Component 
	          {
                    id: menuHighlight
                    
                    Rectangle 
			{
                        id:highlightBar
			color: "#616365"
                        radius: 5
                        width: menu.width; height: menu.currentItem.height
                        /* Animate Highlight customized way */
                        y:listView.currentItem.y;
                        Behavior on y {SpingAnimation {sping: 2; damping:0.01}}

                        /* up/down arrows */
                        Rectangle 
			   {
                            anchors { right: parent.right; rightMargin: 5; }
                            width: 25; height: parent.height
                            color: parent.color

                            Image 
		                {
                                id: arrowImage
                                anchors.centerIn: parent
                                source: "qrc:/images/arrows.png"
                             }

                            states: [
                                State 
								{
                                    when: (menu.currentIndex == 0)&&(menu.currentIndex != (menu.count - 1))
                                    PropertyChanges { target: arrowImage; source: "qrc:/images/arrow_down.png"; }
                                },
                                State 
								{
                                    when: menu.currentIndex == (menu.count - 1)&&(menu.currentIndex != 0)
                                    PropertyChanges { target: arrowImage; source: "qrc:/images/arrow_up.png"; }
                                }
                            ]
                        }
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
                        //menuinfoLoader.source = "../Help.qml"
                    }break;
                }
            }
			event.accepted = true
        }
    }
}
