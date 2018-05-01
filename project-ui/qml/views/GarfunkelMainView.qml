//%
//% This is the Base QML View Of the Garfunkel MainView
//% The Main Screen View is an Instance of this view
//% Designed Jan 06th 2015
//% By Norbert.Tambe@ECOLAB.COM
//%

import QtQuick 1.0
import com.ecolab.components 1.0
//import GarfunkelResourceStrings 0.1
//import "views" //% additional Components


//% Main Window
Rectangle {
	id: garfunkelMain
    anchors.fill: parent
    width: 480
    height: 272
    color: "lightsteelblue" //% change to reflex NGC screen
        
	//% default Properties using  alias
    default property alias content: garfunkelMain.children

    property alias breadcrumb: breadcrumb.text //% text from breadcrumb
    //property alias title: titlebar.text //% Text for title
        
    property bool viewHighlight : true
    property bool setEntireScreenSameFont : true

    //% get screen front from Langauge strings
    property variant screenfont:  "helvetica" // (isTMScreen==true)? AquanomicsLM.GetTMLangaugeFontName() : AquanomicsLM.GetPrimaryLangaugeFontName()
        
	property variant brdcrumbfont : (setEntireScreenSameFont==true) ? screenfont : "helvetica"
    property bool fontBold : false //(isTMScreen==true)? AquanomicsLM.GetTMLangaugeFontBoldStatus() : false
    property bool titleBold : true

    property real hsize : 1/10


    //% Menu Related stuff
    property bool menuHighlightVisible : true
    //property  variant count: menu.count
	property alias menuModel: menu.model
    property alias menuDelegate: menu.delegate
    property alias menuHighlight: menu.highlight


    property alias currentIndex: menu.currentIndex
	property alias source: menuLoader.source
   	property alias item: menuLoader.item
       	
	//% Buttons Properties
    property color buttonFillColor: "darkblue" //"#0082c8"
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
        
         	garfunkelMain.screenfont = "helvetica"  //(isTMScreen==true)? AquanomicsLM.GetTMLangaugeFontName() : AquanomicsLM.GetTMLangaugeFontName()
       
        	garfunkelMain.fontBold = false //(isTMScreen==true)? AquanomicsLM.GetTMLangaugeFontBoldStatus() : false
            brdcrumbfont =  (setEntireScreenSameFont==true) ? screenfont: "helvetica"
        	//console.log("************DONE*******");
   	 }
       

    //% Loader to Load qml files
    Loader {
            id:  menuLoader
            anchors.fill: parent
            source: ""

            onSourceChanged: {
                if (source == "") {
                    menuView.visible = true
                    mainView.focus = true
                } else {
                     menuLoader.focus = true
                }
            }
            onLoaded: menuView.visible = false;
        }

    Connections {
        target:  menuLoader.item
        onGoBack: {
                 menuLoader.source = "";
                 reloadFontProperties()
                 menuView.visible = true
                 menuView.focus = true
                 mainView.focus  = true
        }
    }  

 
    //% Window View
    Rectangle{
             id: menuView
             anchors { fill: parent }
             color: "lightsteelblue"

            //% container to hold GridView
             Item {
                  id: container
                  anchors.fill: parent

                   //% If BreadCrumb is Stubborn: replace Him!
                   /*
                   Text {
                   id: titlebar
                   height: parent.height*hsize
                   width: parent.width
                   anchors { top: parent.top
                                horizontalCenter: parent.horizontalCenter
                                margins: 10
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
                       anchors{ top: parent.top; topMargin: 5
                                //horizontalCenter: parent.horizontalCenter
                                   }
                       width:  parent.width
                       height: parent.height*hsize
                       breadcrumbfont :  brdcrumbfont
                       breadcrumbfontbold : titleBold
                       text : "Title"
                       color: "black"
                   }

                   //% FocusScope for GridView
                   FocusScope {
                          id: mainView
                          width: parent.width
                          height: parent.height
                          focus: true

                          //% Grid Menu View
                          GridMenu {
                                   id: menu
                                   x: 10 //% Make it  center to view screen
                                   anchors {
                                            bottom: parent.bottom
                                            bottomMargin: 2
                                         }
                                   width: menu.cellWidth*3; height: menu.cellHeight*2 + 10
                                   //width: parent.width ; height: 9*parent.height*hsize  //% lol
                                   cellWidth: 153 //160
                                   cellHeight: 100 //90

                                   focus: true
                                   visible: viewHighlight
                                   interactive: parent.activeFocus
                                   //% Use parent custom highlight & delegate
                                   //delegate: menuDelegate
                                   //highlight: menuHighlight
                                   //highlightFollowsCurrentItem: false

                                   //% Select an item from GridMenu


                                   Keys.onReturnPressed: {
                                                         if (!event.isAutoRepeat) {
                                                         garfunkelMain.enterPressed(menu.currentIndex)
                                                         console.log("menu.currentIndex"+menu.currentIndex + " Works")
                                                         event.accepted = true
                                                         }
                                                       }

                          }//% end of GridView
                      } //% end of FocusScope

         }//% Item container ends



         focus: true
         Keys.forwardTo: [parent, menu] //% parent and GridView control Keys
         Keys.onPressed: {
             // disable auto repeat //
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
                 }  // endof switch
             } //endof if

             event.accepted = true
         } // endof keys.onPressed

    }//% MenuView rec ends

} //% garfunkelMain ends
