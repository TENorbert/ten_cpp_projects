//%
//% innerGridView.qml
//%
//% CondorScreen.qml Is an Instance of this View
//%
//% Designed/Implemented Feb 01 2015
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
    property variant screenfont:  "helvetica" // (isTMScreen==true)? GarfunkelLM.GetTMLangaugeFontName() : GarfunkelLM.GetPrimaryLangaugeFontName()
        
	property variant brdcrumbfont : (setEntireScreenSameFont==true) ? screenfont : "helvetica"
    property bool fontBold : false //(isTMScreen==true)? GarfunkelLM.GetTMLangaugeFontBoldStatus() : false
    property bool titleBold : true

    property real hsize : 1/10

    property string arrowImage: "qrc:/images/condor/leftBlueArrow.png"

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
        
         	main.screenfont = "helvetica"  //(isTMScreen==true)? GarfunkelLM.GetTMLangaugeFontName() : GarfunkelLM.GetTMLangaugeFontName()
       
        	main.fontBold = false //(isTMScreen==true)? GarfunkelLM.GetTMLangaugeFontBoldStatus() : false
            brdcrumbfont =  (setEntireScreenSameFont==true) ? screenfont: "helvetica"
        	//console.log("************DONE*******");
   	 }
         
	//% Loader to Load qml scripts
    Loader {
            id:  menuLoader
            anchors.fill: parent
            source: ""

            onSourceChanged: {
                if (source == "") {
                    menuView.visible = true
                    menuView.focus = true
                    mainView.visible = true
                    mainView.focus = true
                } else {
                     menuLoader.focus = true
                }
            }
            onLoaded: menuView.visible = false
        }

    Connections {
        target:  menuLoader.item
        onGoBack: {
             menuLoader.source = ""
             reloadFontProperties()
             menuView.visible = true
             menuView.focus = true
             mainView.visible = true
             mainView.focus = true
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

                    //% Left Arrow
                    LArrowButton{
                                 id: lArrow
                                 lbuttonImage: arrowImage
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
                                   anchors { rightMargin: 2 }

                                   width: menu.cellWidth*3 ; height: menu.cellHeight*2 + 10
                                   cellWidth: 180
                                   cellHeight: 85

                                   focus: true
                                   visible: viewHighlight
                                   interactive: menu.activeFocus
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




                        /*
                          //% Menu View as Grid
                          Rectangle {
                              id: gridviewholder
                              //anchors {left:lArrow.right; right:rArrow.left; leftMargin: 4;
                              //         rightMargin: 4 } // bottom: parent.bottom; bottomMargin: 5}
                              x: 50 //% Make it  center to view screen
                              y: (parent.height - menu.cellHeight*2) - 63
                              width: menu.cellWidth*3 ; height: menu.cellHeight*2 + 10
                              color: "lightsteelblue"

                              GridView {
                                      id: menu
                                      //currentIndex: 0; //% gridView always starts with first index
                                      anchors { fill: parent
                                                //leftMargin: 5
                                                //rightMargin: 5
                                                 topMargin: 2
                                               }
                                      cellWidth: 130 ; cellHeight: 85
                                      focus: true; clip: true
                                      visible: viewHighlight
                                      interactive: menu.activeFocus
                                      //model: menuModel
                                      //flow: GridView.TopToBottom //%View from Top to Bottom
                                      flow: GridView.LeftToRight //%View from Left to Right
                                      highlightFollowsCurrentItem: false //% control highlight by GridView
                                      //% Use parent custom highlight & delegate
                                      //delegate: menuDelegate
                                      //highlight: menuHighlight
                                      //delegate: Item {
                                                      id: menuDelegate
                                                      width: menu.cellWidth; height: menu.cellHeight
                                                      Rectangle {
                                                                id: content
                                                                color: "transparent"
                                                                smooth: true
                                                                anchors.fill: parent; anchors.margins: 5; radius: 12

                                                                //% Text Only Button List View Item
                                                                QMLTextButton {
                                                                         radius: 10
                                                                         //opacity: 0.8
                                                                         smooth: true
                                                                         anchors{ fill: parent; margins: 3 }

                                                                         buttonLabel: name
                                                                         buttonLabelSize: textfontSize //16
                                                                         buttonColor: buttonFillColor
                                                                         borderColor: buttonBorderColor
                                                                        }


                                                     }

                                                      MouseArea {
                                                          id: mouseArea
                                                          anchors.fill: parent

                                                          onClicked: {
                                                              menu.currentIndex = index
                                                              menuDelegate.forceActiveFocus()
                                                          }
                                                      }

                                                      states: State {
                                                          name: "active"; when: menuDelegate.activeFocus
                                                          PropertyChanges { target: content; color: "darkblue"; scale: 1.05 }
                                                      }

                                                      transitions: Transition {
                                                          NumberAnimation { properties: "scale"; duration: 100 }
                                                      }

                                                  }//% End of Delegate

                                      highlight: Item {
                                                       id: menuHighlight
                                                       width: menu.cellWidth; height: menu.cellHeight

                                                          Rectangle {
                                                                    id: highlightcontent
                                                                    color: "transparent"
                                                                    smooth: true
                                                                    anchors.fill: parent; anchors.margins: 5; radius: 10

                                                                    Rectangle {
                                                                               color: "darkblue"
                                                                               radius: 12
                                                                               smooth: true; clip: true
                                                                               x: menu.currentItem.x + 1
                                                                               y: menu.currentItem.y + 2
                                                                               width: menu.cellWidth -15 //- 20; // use gridView.width
                                                                               height: menu.cellHeight -15
                                                                               visible: true

                                                                    }
                                                          }

                                                          MouseArea {
                                                                    id: mouseArea
                                                                    anchors.fill: parent

                                                                    onClicked: {
                                                                       menu.currentIndex = index
                                                                       menuHighlight.forceActiveFocus()

                                                                     }
                                                            }

                                                          states: State {
                                                             name: "highlightActive"; when: menuHighlight.activeFocus
                                                             PropertyChanges { target: highlightcontent; color: "transparent"; scale: 1.05 }
                                                        }

                                                        transitions: Transition {
                                                             NumberAnimation { properties: "scale"; duration: 100 }
                                                        }

                                                    }




                                      //% Select an item from GridMenu
                                      Keys.onReturnPressed: {
                                                            if (!event.isAutoRepeat) {
                                                            main.enterPressed(menu.currentIndex)
                                                            console.log("GridView.currentIndex "+ menu.currentIndex + " Works")
                                                            event.accepted = true
                                                            }
                                      }


                                      //% As soon as you instantiate GridView
                                      Component.onCompleted: {
                                                              positionViewAtIndex(currentIndex, ListView.Contain)

                                                              console.log("GridView.count = "+ menu.count)
                                                              console.log("GridView.currentItem.width= "+ menu.currentItem.width)
                                                              console.log("GridView.currentItem.height= "+ menu.currentItem.height)

                                                            }

                                   }//% end Grid View

                             }//% end of Rectangle

                          */


                    } //% end of FocusScope



            /*
              //% Delagate
              Component{
                        id: menuDelegate
                        Item {
                             id: delegateComponent
                             width: menu.cellWidth; height: menu.cellHeight
                             Rectangle {
                                       id: content
                                       color: "transparent"
                                       smooth: true
                                       anchors.fill: parent; anchors.margins: 5; radius: 12

                                       //% Text Only Button List View Item
                                       QMLTextButton {
                                                radius: 10
                                                //opacity: 0.8
                                                smooth: true
                                                anchors{ fill: parent; margins: 3 }

                                                buttonLabel: name
                                                buttonLabelSize: textfontSize //16
                                                buttonColor: buttonFillColor
                                                borderColor: buttonBorderColor
                                               }


                            }

                             MouseArea {
                                 id: mouseArea
                                 anchors.fill: parent

                                 onClicked: {
                                     menu.currentIndex = index
                                     menudelegate.forceActiveFocus()
                                 }
                             }

                             states: State {
                                 name: "active"; when: menudelegate.activeFocus
                                 PropertyChanges { target: content; color: "darkblue"; scale: 1.05 }
                             }

                             transitions: Transition {
                                 NumberAnimation { properties: "scale"; duration: 100 }
                             }
                        }

              }//% End of Delegate

              // highlight
              Component{
                        id: menuHighlight
                        Item {
                        id: highlightComponent
                        width: menu.cellWidth; height: menu.cellHeight

                        Rectangle {
                                  id: highlightcontent
                                  color: "transparent"
                                  smooth: true
                                  anchors.fill: parent; anchors.margins: 5; radius: 10
                                  //width: menu.cellWidth; height: menu.cellHeight

                                  Rectangle {
                                             color: "darkblue"
                                             radius: 12
                                             smooth: true; clip: true
                                             x: menu.currentItem.x + 1
                                             y: menu.currentItem.y + 2
                                             width: menu.cellWidth -15 //- 20; // use gridView.width
                                             height: menu.cellHeight -15
                                             visible: true

                                  }
                        }

                        MouseArea {
                                  id: mArea
                                  anchors.fill: parent

                                  onClicked: {
                                     menu.currentIndex = index
                                     menuhighlight.forceActiveFocus()

                                   }
                          }

                        states: State {
                           name: "highlightActive"; when: menuhighlight.activeFocus
                           PropertyChanges { target: highlightcontent; color: "transparent"; scale: 1.05 }
                        }

                      transitions: Transition {
                           NumberAnimation { properties: "scale"; duration: 100 }
                      }

                   }

              } // End of HighLight

            */

        } //% end of Item



        GSoftkeysWithIcons {
            id: softkeys
            x: 10
            y: 213
            //anchors.bottom: menu.bottom
            anchors{
                //top: parent.bottom
                topMargin: 10
                rightMargin: 5
                leftMargin: 5
                bottomMargin: 2
            }
            softkeyIconList: ["qrc:/images/ngc/HomeOut.png" , "qrc:/images/ngc/BackOut.png", "qrc:/images/ngc/BlankButtonOut.png", "qrc:/images/ngc/HelpOut.png"]
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
                            main.source ="qrc:/qml//MainScreen.qml"
                        }
                        break;
                    case Qt.Key_F2:
                        {
                            event.accepted = true;
                            console.log("F2: Back to Home!!");
                            main.visible = false;
                            main.focus   = false;
                            main.goBack();
                        }
                        break;
                    case Qt.Key_F3:
                        {
                           // main.goBack(); // Status but just go back for now!!
                       }
                        break;
                    case Qt.Key_F4:
                        {
                            //% for now Go to Page 2 if any
                            main.source ="qrc:/qml//Help.qml"
                        }
                        break;

                }  // endof switch
            }

            event.accepted = true
        } // endof keys.onPressed

      }//% MenuView rec ends

} //% main ends
