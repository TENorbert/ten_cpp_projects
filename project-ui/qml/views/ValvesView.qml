//%
//% ValvesView.qml
//%
//% VMainScreen.qml Is an Instance of this View
//%
//% Designed/Implemented Jan 06th 2015
//% By Norbert.Tambe@ECOLAB.COM
//%

import QtQuick 1.0
import com.ecolab.components 1.0
//import GarfunkelResourceStrings 0.1
import "../views" //% additional Components


//% Main Window
Rectangle {
	id: main
    anchors.fill: parent
 	width: 480  //% Fit for condor Screen
	height: 272 //% fit for condor screen
    color: "lightsteelblue" //% change to reflex NGC screen
        
	//% default Properties using  alias
    default property alias content: main.children

    property alias breadcrumb: breadcrumb.text //% text from breadcrumb
    //property alias title: titlebar.text //% Text for title
    
    //% SoftKeys needed here!
    property alias softKeyIconList: softkeys.softkeyIconList
    property bool softkeysEnabled: true
    /*
    property alias btnIcon1: softkeys.btnIcon1
    property alias btnIcon2: softkeys.btnIcon2
    property alias btnIcon3: softkeys.btnIcon3
    property alias btnIcon4: softkeys.btnIcon4*/

        
    property bool viewHighlight : true
    property bool setEntireScreenSameFont : true

    //% get screen front from Langauge strings
    property variant screenfont:  "helvetica" // (isTMScreen==true)? AquanomicsLM.GetTMLangaugeFontName() : AquanomicsLM.GetPrimaryLangaugeFontName()
        
	property variant brdcrumbfont : (setEntireScreenSameFont==true) ? screenfont : "helvetica"
    property bool fontBold : false //(isTMScreen==true)? AquanomicsLM.GetTMLangaugeFontBoldStatus() : false
    property bool titleBold : true

    property real hsize : 1/10

    property string arrowImage: "qrc:/images/condor/leftBlueArrow.png"  //% Arrow to indicate directions  //right_arrow.png"

    //% Menu Related stuff
    property bool menuHighlightVisible : true
    //property  variant count: menu.count
	property alias menuModel: menu.model
    //property alias menuDelegate: menu.delegate
    //property alias menuHighlight: menu.highlight


    property alias currentIndex: menu.currentIndex
	property alias source: menuLoader.source
   	property alias item: menuLoader.item
       	
	//% Buttons Properties
	property color buttonFillColor: "#0082c8"
    property color buttonBorderColor: "#7A8182"
    property color buttonHighlightColor: "darkblue"
      
	property real textfontSize: 16

    //% signals
    signal goBack()
    signal enterPressed(int currentIndex)

	//% Functions to Relaod Language & font properties
    function reloadFontProperties()
	    {
        	//console.log("************Inside reloadFontProperties*******");
        
         	main.screenfont = "helvetica"  //(isTMScreen==true)? AquanomicsLM.GetTMLangaugeFontName() : AquanomicsLM.GetTMLangaugeFontName()
       
        	main.fontBold = false //(isTMScreen==true)? AquanomicsLM.GetTMLangaugeFontBoldStatus() : false
            brdcrumbfont =  (setEntireScreenSameFont==true) ? screenfont: "helvetica"
        	//console.log("************DONE*******");
   	 }
         
	//% Loader to Load qml scripts
    Loader
          {
        	id: menuLoader
        	anchors.fill: parent
        	source: ""

            onSourceChanged: {
                if(source == "") {
                    menuView.visible = true
                    menuView.focus = true
                    mainView.visible = true
                    mainView.focus = true

                 }else {
                    menuLoader.focus = true
                }
          }
        	onLoaded: menuView.visible = false;
   	 }

    Connections
          {
        	target: menuLoader.item
        	onGoBack: {
                    menuLoader.source = ""; //"qrc:/qml//DMainScreen.qml";
            		reloadFontProperties();
                    menuView.visible = true;
                    menuView.focus = true;
                    mainView.visible = true;
                    mainView.focus = true;
                    //mainView.visible = true
                    //mainView.focus = true //% send FocusScope back to fucus
                    menu.visible = true;
                    menu.focus = true;
        	}
    }

 
    //% Window View
    Rectangle {
            id: menuView
            anchors { fill: parent }
            color: "lightsteelblue"


            //% container to hold GridView
            Item {
                    id: container
                    anchors { fill: parent} //%  margins : 10 
                    //width: parent.width; height: parent.height

                    //% If BreadCrumb is Stubborn: replace it!
                    /*
                    Text {
                    id: titlebar
                    height: parent.height*hsize
                    width: parent.width
                    anchors { top: parent.top
                                horizontalCenter: parent.horizontalCenter
                                topMargins: 3
                           }
                    text: "Title"
                    color: "black"
                    font { family: brdcrumbfont
                             bold: fontbold
                             pixelSize: textfontSize
                          }
                    }
                    */

                    //% Use BreadCrumb Stuff for Screen Title
                    GBreadcrumb {
                       id: breadcrumb
                       anchors{ top: parent.top; topMargin: 2
                                //horizontalCenter: parent.horizontalCenter
                            }
                       width:  parent.width
                       height: parent.height*hsize
                       breadcrumbfont :  brdcrumbfont
                       breadcrumbfontbold : titleBold
                       text : "Title"
                       color: "black"
                   }


                    //% Arrow to Indicate Menu Items navigation
                    //% right Arrow
                    RArrowButton{
                                 id: rArrow
                                 rbuttonImage: arrowImage
                     }

                    //% FocusScope for GridView
                    FocusScope {
                          id: mainView
                          width: parent.width
                          height: parent.height
                          focus: true

                          //% Menu View as Grid
                          GridViewMenu {
                                   id: menu
                                   x: 50 //% Make it  center to view screen
                                   y: (parent.height - menu.cellHeight*2) - 63

                                   anchors {
                                           //fill: parent;
                                           //horizontalCenter: parent.horizontalCenter
                                           //verticalCenter: parent.verticalCenter;
                                           //right: rArrow.left cannot anchor to sibling
                                           //leftMargin: 10
                                           rightMargin: 2
                                           //bottomMargin: 10
                                           //top: parent.top
                                           //topMargin: 10
                                           //bottom : parent.bottom
                                         }

                                   width: menu.cellWidth*3 ; height: menu.cellHeight*2 + 10
                                   cellWidth: 130
                                   cellHeight: 85

                                   focus: true
                                   visible: viewHighlight
                                   interactive: mainView.activeFocus
                                   //% Use parent custom highlight & delegate
                                   //delegate: menuDelegate
                                   //highlight: menuHighlight

                                   //% Select an item from GridMenu
                                   Keys.onReturnPressed: {
                                                         if (!event.isAutoRepeat) {
                                                         main.enterPressed(menu.currentIndex)
                                                         console.log("menu.currentIndex"+menu.currentIndex + " Works")
                                                         event.accepted = true
                                                         }
                                                       }

                          }//% end of GridViewMenu


                    } //% end of FocusScope



            } //% end of Item               


            GSoftkeysWithIcons {
                id: softkeys
                x: 10 //% position at x = 20
                y: 213 //278
                //anchors.bottom: menu.bottom
                anchors{
                    //top: parent.bottom
                    topMargin: 10
                    rightMargin: 2
                    leftMargin: 2
                    bottomMargin: 2
                }
                //TODO : make this as enabel or disable to hide
                //softkeyIconList: ["qrc:/images/home.png", "qrc:/images/help-icon.png", "", ""]
                softkeyIconList: ["qrc:/images/ngc/BlankButtonOut.png" , "qrc:/images/ngc/BackOut.png", "qrc:/images/ngc/BlankButtonOut.png", "qrc:/images/ngc/BlankButtonOut.png"]

            }



        focus: true
        Keys.forwardTo: [parent, menu]
        Keys.onPressed: {
            /* disable auto repeat */
            if (!event.isAutoRepeat) {
                switch (event.key) {   // How about next screen if last index in ListModel conatainer?
                    case Qt.Key_Up:
                        break;
                    case Qt.Key_Right:
                        break;
                    case Qt.Key_Down:
                        break;
                    case Qt.Key_Left:
                        break;
                     //back to Main Menu Screen if F1-F3-F4 pressed //
                    case Qt.Key_F1:
                        {
                            //Use for going home!
                            main.source ="qrc:/qml//MainScreen.qml"
                        }
                        break;
                    case Qt.Key_F2:
                        {
                          //Use for Going back
                        }
                        break;
                    case Qt.Key_F3:
                        {
                           //Leave Blank for Now!!
                       }
                        break;
                    case Qt.Key_F4:
                        {
                             // U should not be able to seek help either at this point!!
                             event.accepted = true
                             //% Just Go to help if any
                             main.source ="qrc:/qml//Help.qml"

                        }
                        break;
                }  // endof switch
            } //endof if

            event.accepted = true
        } // endof keys.onPressed

   }//% MenuView rec ends

} //% main ends
