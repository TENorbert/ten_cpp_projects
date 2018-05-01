//%
//% This is the Base QML View of a Valve
//% Designed Jan 06th 2015
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
    property alias softKeyIconList: valvesoftkeys.softkeyIconList
    property bool softkeysEnabled: true

    property alias btnIcon1: valvesoftkeys.btnIcon1
    property alias btnIcon2: valvesoftkeys.btnIcon2
    property alias btnIcon3: valvesoftkeys.btnIcon3
    property alias btnIcon4: valvesoftkeys.btnIcon4

    // Keys Enabled on default View/State
    property bool    f1Enabled:      true // No Home Key Needed Anyways!!!!
    property bool    f2Enabled:      true
    property bool    f3Enabled:      true
    property bool    f4Enabled:      true

    property bool    valveTestInProgress:      true //Allows to use same key to Switch Off diagnostics during test



   //% Valves Strings
    property alias      temperatureString: tempItem.text
    property alias      conductivityString: condItem.text
    property alias      pWaterStatusString: pstatusItem.text
    property alias      vTimerString    :   timerItem.text
    property  alias     vTestString     :   testItem.text
    property  alias     vStateString    :   stateItem.text

    //% Valve Data
    property  alias    valveTemp            :        tempData.text
    property  alias    valveCond            :        condData.text
    property  alias    valvePStatus         :        pstatusData.text
    property  alias    valveDTimer          :        timerData.text
    property  alias    valveTest            :        testData.text
    property  alias    valveState           :        stateData.text
   //property  alias    valveTotalTime       :         0
   //property  alias    valveTimer           :         0


    property bool setEntireScreenSameFont : true

    //property alias valveDataModel: repeater.model



    //% get screen front from Langauge strings
    property variant screenfont:  "helvetica" // (isTMScreen==true)? GarfunkelLM.GetTMLangaugeFontName() : GarfunkelLM.GetPrimaryLangaugeFontName()
        
	property variant brdcrumbfont : (setEntireScreenSameFont==true) ? screenfont : "helvetica"
    property bool fontBold : false //(isTMScreen==true)? GarfunkelLM.GetTMLangaugeFontBoldStatus() : false
    property bool titleBold : true

    property real hsize : 1/10


   //% Button Properties
	property alias source: menuLoader.source
   	property alias item: menuLoader.item
       	
	//% Buttons Properties
    property color buttonFillColor: "lightsteelblue" //"#0082c8"
    property color buttonBorderColor: "#7A8182"
    property color buttonHighlightColor: "darkblue"
      
	property real textfontSize: 16

    //% signals
    signal goBack()

	//% Functions to Relaod Language & font properties
    function reloadFontProperties()
	    {
        	//console.log("************Inside reloadFontProperties*******");
        
         	main.screenfont = "helvetica"  //(isTMScreen==true)? GarfunkelLM.GetTMLangaugeFontName() : GarfunkelLM.GetTMLangaugeFontName()
       
        	main.fontBold = false //(isTMScreen==true)? GarfunkelLM.GetTMLangaugeFontBoldStatus() : false
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
            onSourceChanged:{
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
                    menuLoader.source = "" //"qrc:/qml//VMainScreen.qml";
                    reloadFontProperties()
                    menuView.visible = true
                    menuView.focus = true
                    mainView.visible = true
                    mainView.focus = true

        	}

    }

    Connections
              {
                target: diagcontext
                onIsValveTestChanged:
                            {
                                valveTestInProgress =  diagcontext.isValveTest
                            }
                //% Really not need F1-Key here!
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
                                 valvesoftkeys.btnIcon1 = "qrc:/images/ngc/BlankButtonOut.png";
                                }
                                else if (diagcontext.buttonOneString == "HOME") {
                                     valvesoftkeys.btnIcon1 = "qrc:/images/ngc/HomeOut.png";
                                }
                            }
                onButtonTwoStringChanged:
                            {
                                if (diagcontext.buttonTwoString == "") {
                                    valvesoftkeys.btnIcon2 = "qrc:/images/ngc/BlankButtonOut.png";
                                }
                                else if (diagcontext.buttonTwoString == "BACK") {
                                    valvesoftkeys.btnIcon2 = "qrc:/images/ngc/BackOut.png";
                                }
                            }
                onButtonThreeStringChanged:
                            {

                                if (diagcontext.buttonThreeString == "") {
                                    valvesoftkeys.btnIcon3 = "qrc:/images/ngc/BlankButtonOut.png";
                                }
                                else if (diagcontext.buttonThreeString == "ON") {
                                    valvesoftkeys.btnIcon3 = "qrc:/images/ngc/CheckOut.png";

                                }
                                else if(diagcontext.buttonThreeString == "CANCEL") {
                                  valvesoftkeys.btnIcon3 = "qrc:/images/ngc/CancelOut.png";
                                }

                            }
                onButtonFourStringChanged:
                            {
                                if (diagcontext.buttonFourString == "") {
                                    valvesoftkeys.btnIcon4 = "qrc:/images/ngc/BlankButtonOut.png";
                                }       
                                else if (diagcontext.buttonFourString == "HELP") {
                                    valvesoftkeys.btnIcon4 = "qrc:/images/ngc/HelpOut.png";
                                }
                                else if(diagcontext.buttonFourString == "OFF") {
                                  valvesoftkeys.btnIcon4 = "qrc:/images/ngc/CancelOut.png";
                                }
                            }
     }


    //% Valves Data Updates
    Connections
              {
                target: diagcontext

                onValveWaterTempChanged:
                            {
                               var vTemp = diagcontext.valveWaterTemp //Temp in Farenheight(F)
                                valveTemp = "" + vTemp + " F"
                             }
                onValveWaterConductivityChanged:
                            {
                                var vCond = diagcontext.valveWaterConductivity //Temp in uS/cm
                                valveCond = "" + vCond + "uS/cm"
                            }
                onValveWaterPressureSwitchStatusChanged:
                            {
                                var vPStatus = (diagcontext.valveWaterPressureSwitchStatus == 1) ? "OPEN" : "CLOSED"
                                valvePStatus = "" + vPStatus + ""
                            }

                onValveDelayTimerChanged :
                           {
                                var vDTimer = diagcontext.valveDelayTimer;
                                valveDTimer = "" + vDTimer + " s"
                            }

                onValveTotalTimeChanged :
                            {
                                var vTotalTime = diagcontext.valveTotalTime;
                                //valveDataModel.setProperty(index, {"valveItem":"Total Time", "valveData": vTotalTime })

                             }

                onValveTimerChanged :
                            {
                                var vTimer = diagcontext.valveTimer;
                                //valveDataModel.setProperty(index, {"valveItem":"Test Timer", "valveData": vTimer })
                            }

                onValveTestStringChanged:
                            {
                                var vTest = diagcontext.valveTestString;
                                valveTest = "" + vTest + ""
                            }
                onValveStateStringChanged:
                            {
                                var vState = diagcontext.valveStateString;
                                valveState =  "" + vState + ""
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
            anchors { fill: parent}

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







           //% Holds all the inner Windows
           Rectangle {
                    anchors {fill: parent;  topMargin: 50; rightMargin: 10; leftMargin: 10
                            bottomMargin: 10
                    }
                    //x: 15; y: 220
                    //y: (parent.height - gridview.height*2) - 70
                   // width: 390 ; height: 140 //160
                    clip: true
                    radius: 10
                    color: buttonFillColor
                    //gradient: Gradient {
                    //            GradientStop { position: 0.0; color: Qt.lighter(buttonFillColor,1.25) }
                    //            //GradientStop { position: 0.67; color: Qt.darker(buttonFillColor,1.3) }
                    //            GradientStop { position: 1.0; color: Qt.darker(buttonFillColor,0.9) }
                    //}

                    Item{
                            x: 0
                            y: -55
                            //anchors.fill: parent
                            //% Temprature
                            Rectangle {
                                id: tempId
                                x: 10; y: breadcrumb.height + 30
                                width: 140; height: 75
                                radius: 10
                                smooth: true
                                border.width: 1
                                gradient: Gradient {
                                    GradientStop { position: 0.0; color: "#0082c8" }
                                    //GradientStop { position: 1.0; color: "transparent" }
                                }
                                 Text {
                                 id: tempItem
                                 text: ""
                                 anchors { top: parent.top; leftMargin:2; topMargin:2; fill: parent }
                                 font.pixelSize: textfontSize
                                 font.family: screenfont
                                 font.bold: fontBold
                                 color: "white"
                                 }

                                 Text {
                                 id: tempData
                                 anchors{ top:tempItem.bottom; topMargin: 2; centerIn: parent; bottomMargin: 2 }
                                 text: ""
                                 font.pixelSize: textfontSize
                                 font.family: screenfont
                                 font.bold: fontBold
                                 color: "white"
                                 }
                            }

                            //% Conductivity
                            Rectangle {
                                id: condId
                                x: 10 + 140 + 10; y: breadcrumb.height + 30
                                anchors{left: tempId.right; leftMargin: 10}
                                width: 140; height: 75
                                radius: 10
                                smooth: true
                                border.width: 1
                                gradient: Gradient {
                                    GradientStop { position: 0.0; color: "#0082c8" }
                                    //GradientStop { position: 1.0; color: "transparent" }
                                }
                                 Text {
                                 id: condItem
                                 text: ""
                                 anchors { top: parent.top; leftMargin:2; topMargin:2; fill: parent }
                                 font.pixelSize: textfontSize
                                 font.family: screenfont
                                 font.bold: fontBold
                                 color: "white"
                                 }

                                 Text {
                                 id: condData
                                 anchors{ top:condItem.bottom; topMargin: 2; centerIn: parent; bottomMargin: 2 }
                                 text: ""
                                 font.pixelSize: textfontSize
                                 font.family: screenfont
                                 font.bold: fontBold
                                 color: "white"
                                 }
                            }

                            //% Pressure Status
                            Rectangle {
                                id: pstatusId
                                x: 10 + 140*2 + 10*2; y: breadcrumb.height + 30
                                anchors{left: condId.right; leftMargin: 10}
                                width: 140; height: 75
                                radius: 10
                                smooth: true
                                border.width: 1
                                gradient: Gradient {
                                    GradientStop { position: 0.0; color: "#0082c8" }
                                    //GradientStop { position: 1.0; color: "transparent" }
                                }
                                 Text {
                                 id: pstatusItem
                                 text: ""
                                 anchors { top: parent.top; leftMargin:2; topMargin:2; fill: parent }
                                 font.pixelSize: textfontSize
                                 font.family: screenfont
                                 font.bold: fontBold
                                 color: "white"
                                 }

                                 Text {
                                 id: pstatusData
                                 anchors{ top:pstatusItem.bottom; topMargin: 2; centerIn: parent; bottomMargin: 2 }
                                 text: ""
                                 font.pixelSize: textfontSize
                                 font.family: screenfont
                                 font.bold: fontBold
                                 color: "white"
                                 }
                            }

                            //% Valve Timer
                            Rectangle {
                                id: timerId
                                x: 10; y: breadcrumb.height + 30 + 75 + 10
                                width: 140; height: 75
                                radius: 10
                                smooth: true
                                border.width: 1
                                gradient: Gradient {
                                    GradientStop { position: 0.0; color: "#0082c8" }
                                    //GradientStop { position: 1.0; color: "transparent" }
                                }
                                 Text {
                                 id: timerItem
                                 text: ""
                                 anchors { top:timerId.top; leftMargin:2; topMargin:2; fill: parent }
                                 font.pixelSize: textfontSize
                                 font.family: screenfont
                                 font.bold: fontBold
                                 color: "white"
                                 }

                                 Text {
                                 id: timerData
                                 anchors{ top:timerItem.bottom; topMargin: 2; centerIn: parent; bottomMargin: 2 }
                                 text: ""
                                 font.pixelSize: textfontSize
                                 font.family: screenfont
                                 font.bold: fontBold
                                 color: "white"
                                 }
                            }

                            //% Valve Test
                            Rectangle {
                                id: testId
                                x: 10 + 140 + 10; y: breadcrumb.height + 30 + 75 + 10
                                anchors{left: timerId.right; leftMargin: 10}
                                width: 140; height: 75
                                radius: 10
                                smooth: true
                                border.width: 1
                                gradient: Gradient {
                                    GradientStop { position: 0.0; color: "#0082c8" }
                                    //GradientStop { position: 1.0; color: "transparent" }
                                }
                                 Text {
                                 id: testItem
                                 text: ""
                                 anchors { top: testId.top; leftMargin:2; topMargin:2; fill: parent }
                                 font.pixelSize: textfontSize
                                 font.family: screenfont
                                 font.bold: fontBold
                                 color: "white"
                                 }

                                 Text {
                                 id: testData
                                 anchors{ top:testItem.bottom; topMargin: 2; centerIn: parent; bottomMargin: 2 }
                                 text: ""
                                 font.pixelSize: textfontSize
                                 font.family: screenfont
                                 font.bold: fontBold
                                 color: "white"
                                 }
                            }

                            //% Valve State
                            Rectangle {
                                id: stateId
                                x: 10 + 140*2 + 10*2; y: breadcrumb.height + 30 + 75 + 10
                                anchors{left: testId.right; leftMargin: 10}
                                width: 140; height: 75
                                radius: 10
                                smooth: true
                                border.width: 1
                                gradient: Gradient {
                                    GradientStop { position: 0.0; color: "#0082c8" }
                                    //GradientStop { position: 1.0; color: "transparent" }
                                }
                                 Text {
                                 id: stateItem
                                 text: ""
                                 anchors { top: stateId.top; leftMargin:2; topMargin:2; fill: parent }
                                 font.pixelSize: textfontSize
                                 font.family: screenfont
                                 font.bold: fontBold
                                 color: "white"
                                 }

                                 Text {
                                 id: stateData
                                 anchors{ top:stateItem.bottom; topMargin: 2; centerIn: parent; bottomMargin: 2 }
                                 text: ""
                                 font.pixelSize: textfontSize
                                 font.family: screenfont
                                 font.bold: fontBold
                                 color: "white"
                                 }
                              }


                    }

               }


        }//% Item container ends



        GSoftkeysWithIcons {
            id: valvesoftkeys
            x: 10 //% position at x = 20
            y: 213
            //anchors.bottom: menu.bottom
            anchors{
                //top: parent.bottom
                topMargin: 10
                rightMargin: 2
                leftMargin: 2
                bottomMargin: 2
            }
            //softkeyIconList: ["qrc:/images/home.png", "qrc:/images/back-icon.png", "qrc:/images/on.png", "qrc:/images/help-icon.png"]
            //softkeyIconList: ["", "qrc:/images/back-icon.png", "qrc:/images/on.png", ""]
            softkeyIconList: ["qrc:/images/ngc/BlankButtonOut.png", "qrc:/images/ngc/BackOut.png", "qrc:/images/ngc/CheckOut.png", "qrc:/images/ngc/BlankButtonOut.png"]
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
                           {   //% Using this for now only for debugging
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
                             else if (valveTestInProgress)
                           {
                               //Disabling Diagnostics Mode
                                console.log("ValveTestRequest ValveId = " + diagcontext.valveId + "key: F3 Again");
                                diagcontext.valveDiagTestRequest = false;
                           }
                       }
                        break;
                    case Qt.Key_F4:
                        {
                            event.accepted = true
                            if(f4Enabled)
                            {
                               // NOT Needed key!!
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
