//%
//% This is the Base QML View of a Valve
//% Designed Jan 06th 2015
//% By Norbert.Tambe@ECOLAB.COM
//%

import QtQuick 1.0
import com.ecolab.components 1.0
//import AquanomicsResourceStrings 0.1
//import "views" //% additional Components


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
    property alias softKeyIconList: valvesoftkeys.softkeyIconList
    property bool softkeysEnabled: true

    property alias btnIcon1: valvesoftkeys.btnIcon1
    property alias btnIcon2: valvesoftkeys.btnIcon2
    property alias btnIcon3: valvesoftkeys.btnIcon3
    property alias btnIcon4: valvesoftkeys.btnIcon4

    // Keys Enabled on default View/State
    property bool    f1Enabled:      true // permenetly disable Home key
    property bool    f2Enabled:      true
    property bool    f3Enabled:      true
    property bool    f4Enabled:      true

    //% Valve Data
    property real       vTemp:          0
    property real       vCond:          0
    property  string    vPStatus  :    ""
    property int        vDTimer:        0
    property  int       vTotalTime :    0
    property  int       vTimer:         0

    property  string    vTest     :    ""
    property  string    vState    :    ""


    property bool setEntireScreenSameFont : true

    property alias valveDataModel: repeater.model



    //% get screen front from Langauge strings
    property variant screenfont:  "helvetica" // (isTMScreen==true)? AquanomicsLM.GetTMLangaugeFontName() : AquanomicsLM.GetPrimaryLangaugeFontName()
        
	property variant brdcrumbfont : (setEntireScreenSameFont==true) ? screenfont : "helvetica"
    property bool fontBold : false //(isTMScreen==true)? AquanomicsLM.GetTMLangaugeFontBoldStatus() : false
    property bool titleBold : true

    property real hsize : 1/10


   //% Button Properties
	property alias source: menuLoader.source
   	property alias item: menuLoader.item
       	
	//% Buttons Properties
	property color buttonFillColor: "#0082c8"
    property color buttonBorderColor: "#7A8182"
    property color buttonHighlightColor: "darkblue"
      
	property real textfontSize: 16

    //% signals
    signal goBack()

	//% Functions to Relaod Language & font properties
    function reloadFontProperties()
	    {
        	//console.log("************Inside reloadFontProperties*******");
        
         	main.screenfont = "helvetica"  //(isTMScreen==true)? AquanomicsLM.GetTMLangaugeFontName() : AquanomicsLM.GetTMLangaugeFontName()
       
        	main.fontBold = false //(isTMScreen==true)? AquanomicsLM.GetTMLangaugeFontBoldStatus() : false
            brdcrumbfont =  (setEntireScreenSameFont==true) ? screenfont: "helvetica"
        	//console.log("************DONE*******");
   	 }




    //% Function to convert Temprature
    //function tempConvert (degCentTemp, degFahTemp) { }
         
	//% Loader to Load qml scripts
    Loader
          {
        	id: menuLoader
        	anchors.fill: parent
        	source: ""
        	onSourceChanged: menuLoader.focus = true
        	onLoaded: menuView.visible = false;
   	 }

    Connections
          {
        	target: menuLoader.item

        	onGoBack: {
                    menuLoader.source = "qrc:/qml//VMainScreen.qml";
                    reloadFontProperties();
                    menuView.visible = true;
                    menuView.focus = true
                    mainView.visible = true
                    mainView.focus = true

        	}

    }

    Connections
              {
                target: diagcontext
                onKey1EnabledChanged:
                            {
                                f1Enabled =  diagcontext.key1Enabled
                            }
                onKey2EnabledChanged:
                            {
                                f2Enabled =  diagcontext.key2Enabled
                            }
                onKey3EnabledChanged:
                            {
                                f3Enabled =  diagcontext.key3Enabled
                            }

                onButtonOneStringChanged:
                            {
                                if (diagcontext.buttonOneString == "") {
                                 valvesoftkeys.btnIcon1 = "";
                                }
                                else if (diagcontext.buttonOneString == "HOME") {
                                     valvesoftkeys.btnIcon1 = "qrc:/images/home.png";
                                }
                            }
                onButtonTwoStringChanged:
                            {
                                if (diagcontext.buttonTwoString == "") {
                                    valvesoftkeys.btnIcon2 = "";
                                }
                                else if (diagcontext.buttonTwoString == "BACK") {
                                    valvesoftkeys.btnIcon2 = "qrc:/images/back-icon.png";
                                }
                            }
                onButtonThreeStringChanged:
                            {

                                if (diagcontext.buttonThreeString == "") {
                                    valvesoftkeys.btnIcon3 = "";
                                }
                                else if (diagcontext.buttonThreeString == "On") {
                                    valvesoftkeys.btnIcon3 = "qrc:/images/on.png";

                                }

                            }
                onButtonFourStringChanged:
                            {
                                if (diagcontext.buttonFourString == "") {
                                    valvesoftkeys.btnIcon4 = "";
                                }
                                else if(diagcontext.buttonFourString == "OFF") {
                                  valvesoftkeys.btnIcon4 = "qrc:/images/off.png";
                                }
                                else if (diagcontext.buttonFourString == "HELP") {
                                    valvesoftkeys.btnIcon4 = "qrc:/images/help-icon.png";
                                }
                            }
     }






 
    //% Window View
    Rectangle {
             id: menuView
             anchors { fill: parent }
             color: "steelblue"

        //% container to hold GridView
        Item {
            id: container
            anchors { fill: parent} //;  margins : 10 }
            //width: parent.width; height: parent.height


           //% Use BreadCrumb Stuff for Screen Title
           OPLBreadcrumb {
               id: breadcrumb
               anchors{ top: parent.top; topMargin: 5
                        //horizontalCenter: parent.horizontalCenter
                           }
               width:  parent.width
               height: parent.height*hsize
               breadcrumbfont :  brdcrumbfont
               breadcrumbfontbold : titleBold
               text : "Title"
               color: "white"
           }

           //% Holds all the inner Windows
           Rectangle {
                    anchors {fill: parent;  topMargin: 50; rightMargin: 10; leftMargin: 10
                            bottomMargin: 10
                    }
                    x: 15; y: 220
                    //y: (parent.height - gridview.height*2) - 70
                    width: 395 ; height: 160

                    clip: true
                    gradient: Gradient {
                                        GradientStop { position: 0.0; color: Qt.lighter(buttonFillColor,1.25) }
                                        GradientStop { position: 0.67; color: Qt.darker(buttonFillColor,1.3) }
                    }

                   Grid{
                        rows: 2
                        columns: 3
                        spacing: 10

                        Repeater {
                            id: repeater
                            model: valveDataModel


                            Rectangle {
                                width: 145; height: 80
                                radius: 10
                                smooth: true
                                border.width: 1
                                gradient: Gradient {
                                    GradientStop { position: 0.0; color: "lightsteelblue" }
                                    GradientStop { position: 1.0; color: "transparent" }
                                }
                                 Text {
                                 id: texttitle
                                 text: valveItem
                                 anchors { top: parent.top; leftMargin:2; topMargin:2; fill: parent }
                                 font.pixelSize: textfontSize
                                 font.family: screenfont
                                 font.bold: fontBold
                                 color: "white"
                                 }

                                 Text {
                                 id: textlabel
                                 anchors{ top:texttitle.bottom; topMargin: 2; centerIn: parent; bottomMargin: 2 }
                                 text: valveData
                                 font.pixelSize: textfontSize
                                 font.family: screenfont
                                 font.bold: fontBold
                                 color: "white"
                                 }
                            }
                        }

                    }
             }

         }//% Item container ends


        OPLSoftkeysWithIcons {
            id: valvesoftkeys
            x: 20 //% position at x = 20
            y: 222
            //anchors.bottom: menu.bottom
            anchors{
                //top: parent.bottom
                topMargin: 10
                rightMargin: 5
                leftMargin: 5
                bottomMargin: 2
            }
            //softkeyIconList: ["qrc:/images/home.png", "qrc:/images/back-icon.png", "qrc:/images/on.png", "qrc:/images/help-icon.png"]
            softkeyIconList: ["", "qrc:/images/back-icon.png", "qrc:/images/on.png", ""]
        }



//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%
//%   MAIN FOCUS OF THE SCREEN
//%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

        focus: true
        Keys.forwardTo: [parent, menu ]
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
                           event.accepted = true
                           if(f1Enabled)
                           {
                                console.log("To Main Menu key: F1");
                                main.source ="qrc:/qml//MainScreen.qml"
                           }
                        }
                        break;
                    case Qt.Key_F2:
                        {
                          event.accepted = true
                          if(f2Enabled)
                          {
                                console.log("Back To Main Menu key: F2");
                                main.goBack();
                          }
                        }
                        break;
                    case Qt.Key_F3:
                        {
                           event.accepted = true
                           if(f3Enabled)
                           {
                                //event.accepted = true
                                //Enable Diagnostics Mode
                                console.log("ValveTestRequest ValveId = " + diagcontext.valveId + " key: F3");
                                diagcontext.valveDiagTestRequest = true;

                            }
                       }
                        break;
                    case Qt.Key_F4:
                        {
                            event.accepted = true
                            if(f4Enabled)
                            {
                               //% Just Go to help if any for now
                               // main.source ="qrc:/qml//Help.qml"
                               //Disabling Diagnostics Mode
                                console.log("ValveTestRequest ValveId = " + diagcontext.valveId + " key: F4");
                                diagcontext.valveDiagTestRequest = false;
                             }

                        }
                        break;
                }  // endof switch
            } //endof if

            event.accepted = true
        } // endof keys.onPressed







/*
         focus: true
         Keys.forwardTo: [parent] //% parent control Keys
         Keys.onPressed: {
             if (!event.isAutoRepeat) {  // disable auto repeat
                 switch (event.key) {
                     case Qt.Key_F1:
                         main.source = "qrc:/qml//MainScreen.qml";
                         break;
                     case Qt.Key_F2:                        
                        main.goBack();

                         break;
                     case Qt.Key_F3:

                         break;
                     case Qt.Key_F4:
                         main.source ="qrc:/qml//Help.qml"
                         event.accepted = true
                         break;
                 }  // endof switch
             } //endof if

             event.accepted = true
         } // endof keys.onPressed
*/

    }//% MenuView rec ends


} //% main ends
