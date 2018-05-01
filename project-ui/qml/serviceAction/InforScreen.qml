//%*********************************************************************
//%
//%     IOBoardsScreen.qml
//%
//%*********************************************************************

import QtQuick 1.0
import com.ecolab.components 1.0
//import GarfunkelResourceStrings 0.1
import "../views"

//Main Window
Rectangle {
        id: infomain
        anchors.fill: parent
        width: 480
        height: 270
        color: "lightsteelblue"

        //parent properties

        // Keys Enabled on default View/State
        property bool    f1Enabled:      true
        property bool    f2Enabled:      true
        property bool    f3Enabled:      true
        property bool    f4Enabled:      true


        //% Buttons Properties
        property color buttonFillColor: "#0082c8"

        //% Text Properties
        property bool viewHighlight : true
        property bool setEntireScreenSameFont : true

        property real textfontSize: 16
        property variant screenfont:  "helvetica" //(isTMScreen==true)? GarfunkelLM.GetTMLangaugeFontName() : GarfunkelLM.GetPrimaryLangaugeFontName()

        property variant brdcrumbfont : (setEntireScreenSameFont==true) ? screenfont : "helvetica"
        property bool fontBold : false //(isTMScreen==true)? GarfunkelLM.GetTMLangaugeFontBoldStatus() : false
        property bool titleBold : true


        //% Valve Infos
         property  string      temperatureString  :   "Temperature"
         property  string      conductivityString :   "Conductivity"
         property  string      pWaterStatusString :   "Water Pressure Switch Status"
         property  string      vStateString     :   "Valve State"
         property  string      vTimerString     :   "Timer"
         property  string      vTestString      :   "Valve Test"


         //% Valve Data
         property   string    valveTemp            :   "0 F"
         property   string    valveCond            :   "0 uS/cm"
         property   string    valvePStatus         :   "CLOSE"
         property  string     valveState           :   "CLOSE"
         property  string     valveDTimer          :   "0 s"
         property  string     valveTest            :   "NONE"


        //Loader properties
        property alias source: viewLoader.source
        property alias item: viewLoader.item

        //% signals
        signal goBack()


        Loader {
                id: viewLoader
                anchors.fill: parent
                source: ""

                onSourceChanged: {
                    if (source == "") {
                        mainView.visible = true
                        mainView.focus = true
                    } else {
                        viewLoader.focus = true
                    }
                }
                onLoaded: mainView.visible = false;
            }

        Connections {
            target: viewLoader.item
            onGoBack: {
                viewLoader.source = "";
                //reloadFontProperties()
                mainView.visible = true
                mainView.focus = true
            }
        }



        //%Main View
        Rectangle {
              id: mainView
              anchors.fill: parent
              color: "lightsteelblue"
              radius: 10

              Item {
                      id: container
                      anchors.fill: parent
                      //Title
                      //% Use BreadCrumb Stuff for Screen Title
                      GBreadcrumb {
                          id: breadcrumb
                          anchors{ top: parent.top; topMargin: 5
                                   //horizontalCenter: parent.horizontalCenter
                                      }
                          width:  parent.width
                          height: parent.height/10
                          breadcrumbfont :  brdcrumbfont
                          breadcrumbfontbold : titleBold
                          text : "Valve Diagnostics"
                          color: "black"
                      }


                      //menu view
                      Rectangle {
                             id: infoScreenView
                             x: 8
                             y: 40
                             width: 467
                             height: 200
                             color: "lightsteelblue"

                             ColumnTextView {
                                            id: textviewcolumn
                                            //anchors.fill: parent
                                            //textWidth: 250
                                            /*
                                            //Set properties
                                            textOneTitle : temperatureString
                                            textOneData  : valveTemp

                                            textTwoTitle : conductivityString
                                            textTwoData  : valveCond

                                            textThreeTitle: pWaterStatusString
                                            textThreeData : valvePStatus

                                            textFourTitle: vStateString
                                            textFourData : valveState

                                            textFiveTitle: vTimerString
                                            textFiveData : valveDTimer

                                            textSixTitle: vTestString
                                            textSixData : valveTest

                                            */
                             }

                      }


                 }


        GSoftkeysWithIcons {
                          id: thissoftkeys
                          x: 10
                          y: 213
                          anchors{
                                //top: parent.bottom
                            topMargin: 10
                            rightMargin: 2
                            leftMargin: 2
                            bottomMargin: 2
                          }

                          softkeyIconList: ["qrc:/images/ngc/HomeOut.png", "qrc:/images/ngc/BackOut.png",
                               "qrc:/images/ngc/BlankButtonOut.png","qrc:/images/ngc/HelpOut.png"						]
            }


     }

//%*****************************************************************
//%
//%     SCREEN FOCUS
//%
//%*****************************************************************

        focus: true
        Keys.forwardTo: [parent]
        Keys.onPressed: {
            // disable auto repeat //
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
                        {
                           event.accepted = true
                           if(f1Enabled)
                           {
                                console.log("To Main Menu key: F1");
                                infomain.source ="qrc:/qml//MainScreen.qml"
                           }
                        }
                        break;
                    case Qt.Key_F2:
                        {
                          event.accepted = true
                          if(f2Enabled)
                          {
                                console.log("Back To Main Menu key: F2");
                                infomain.goBack();
                          }
                        }
                        break;
                    case Qt.Key_F3:
                        {
                           event.accepted = true
                           if(f3Enabled)
                           {
                                //Add key funtionality
                            }
                       }
                        break;
                    case Qt.Key_F4:
                        {
                            event.accepted = true
                            if(f4Enabled)
                            {
                               console.log("Help Key : F4");
                               infomain.source ="qrc:/qml//Help.qml"
                             }

                        }
                        break;
              	   } 
            	} 

            event.accepted = true
        }



}
