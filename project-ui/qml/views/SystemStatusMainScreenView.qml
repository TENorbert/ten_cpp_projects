/*******************************************************
** SystemStatusMainScreenView.qml
**
********************************************************/

import QtQuick 1.0
import com.ecolab.components 1.0
import "../views"

Rectangle {
    id: sstatscreen
    anchors.fill: parent
    width: 480
    height: 272
    color: "lightsteelblue"

    default property alias content: main.children

   // property alias breadcrumb: breadcrumb.text

/*  property alias softKeyIconList: softkeys.softkeyIconList
    property alias btnIcon1: softkeys.btnIcon1
    property alias btnIcon2: softkeys.btnIcon2
    property alias btnIcon3: softkeys.btnIcon3
    property alias btnIcon4: softkeys.btnIcon4*/
    property bool softkeysEnabled: false

    property bool viewHighlight : true
    property alias menuModel: menu.model
    property alias menuDelegate: menu.delegate
    property alias menuHighlight: menu.highlight
    property alias currentIndex: menu.currentIndex
    property int menuleftMargin : 10
    property alias errorText: errorText.text
    property alias source: menuLoader.source
    property alias item: menuLoader.item
    //propert  variant count: menu.count
    property bool setEntireScreenSameFont : true
    property variant sstatscreenfont:  "helvetica" // (isTMScreen==true)? AquanomicsLM.GetTMLangaugeFontName() : AquanomicsLM.GetPrimaryLangaugeFontName()
    property variant brdcrumbfont : (setEntireScreenSameFont==true) ?  sstatscreenfont : "helvetica"
    property bool fontBold : false //(isTMScreen==true)? AquanomicsLM.GetTMLangaugeFontBoldStatus() : false
    
    property bool menuHighlightVisible : true

    property real hfrac : 1/10
    property string rbImage: "qrc:/images/right_arrow.png"


    property color buttonFillColor: "#0082c8"
    property color buttonBorderColor: "#7A8182"

    property color buttonHighlightColor: "darkblue"

    property real textfontSize: 12

    //Navigation ppty
   // property real sstatscreenNavWidth: 50 //sstatscreenNavWidth
    //property real sstatscreenNavHeight: 50 //sstatscreenNavHeight



    signal goBack()
    signal enterPressed(int currentIndex)

    function reloadFontProperties()
    {
        //console.log("************Inside reloadFontProperties*******");
        
        sstatscreen.sstatscreenfont = "helvetica"  //(isTMScreen==true)? AquanomicsLM.GetTMLangaugeFontName() : AquanomicsLM.GetTMLangaugeFontName()
       
        sstatscreen.fontBold = false //(isTMScreen==true)? AquanomicsLM.GetTMLangaugeFontBoldStatus() : false
        brdcrumbfont =  (setEntireScreenSameFont==true) ? sstatscreenfont: "helvetica"
        //console.log("************DONE*******");
    }

    Loader {
        id: menuLoader
        anchors.fill: parent
        source: ""

        onSourceChanged: menuLoader.focus = true
        onLoaded: menuView.visible = false;
    }
    Connections {
        target: menuLoader.item
        onGoBack: {
            menuLoader.source = "";
            reloadFontProperties();
            menuView.visible = true
            menuView.focus = true
        }
    }

  // Window Title
    Rectangle {
              id: titlebar
              height: parent.height*hfrac; width: parent.width
              anchors{
                      horizontalCenter: parent.horizontalCenter
                      leftMargin: 4; rightMargin: 4
              }
              color: "steelblue"; radius: 10
              Text{
                  id: titletext
                  anchors.centerIn: titlebar
                  text: "System Menu"
                  font.pixelSize: 16
                  color: "white"
              }
    }





   // Right Arrow
  /*  Rectangle {
         id: rightarrow
         width: 55; height: 2*parent.height*hfrac
         //anchors.left: submenu.right
         anchors.rightMargin: 5
         anchors.verticalCenter: sstatscreen.verticalCenter
         anchors.topMargin: 20
         anchors.bottomMargin: 20
         radius: 10
         color: "darkblue"
         gradient: Gradient {
                 GradientStop { position: 0.0; color: Qt.lighter("steelblue",1.25) }
                 GradientStop { position: 0.67; color: Qt.darker("steelblue",1.3) }
             }
         x: 420
         Image{
           id: rarrowimage
           anchors.centerIn: rightarrow
           source: rbImage
         }

       }
   */

    RArrowButton{
         id: rightarrowB
         width: 20; height: 2*parent.height*hfrac
         anchors.rightMargin: 5
         anchors.verticalCenter: sstatscreen.verticalCenter
         anchors.topMargin: 20
         anchors.bottomMargin: 20
         radius: 10
         x: 420
         color: "darkblue"
         rbuttonImage: rbImage
         gradient: Gradient {
                 GradientStop { position: 0.0; color: Qt.lighter("steelblue",1.25) }
                 GradientStop { position: 0.67; color: Qt.darker("steelblue",1.3) }
             }
    }

     // system Status Menu
    Rectangle {
        id: menuView
        //anchors.fill: parent
        width: 400; height: 7*parent.height*hfrac - 10
        color: "steelblue"
        anchors.right: rightarrowB.left
        anchors.rightMargin: 10
        anchors.top: titlebar.bottom
        anchors.topMargin: 5
        //x: 15; y: 5

     Item {
            id: container
            anchors { fill: parent} //; margins: 10; }

          /* Item  embedded in an item */
          Item {
            id: main
            anchors {
                    fill: parent
                    //verticalCenter: parent.verticalCenter
                    //horizontalCenter:  parent.horizontalCenter
                    top: parent.top
                    topMargin: 5
                    //rightMargin: 5
                    //leftMargin: 15
                    //topMargin: 35
                    bottomMargin: (breadcrumb.text == "" ? 2 : 5) //(footerinfo.text == "" ? 1 : (headerinfo.text == "") ? 5: 9)
                    bottom :  (softkeysEnabled == true ? softkeys.top : parent.bottom)
                   }

           /* The menu */
            GridView {
                    id: menu
                    anchors { fill: parent
                            leftMargin: 10
                            rightMargin: 10
                            bottom : parent.bottom
                            bottomMargin: 5
                            top: parent.top
                            topMargin: 5
                    }

                    delegate: menuDelegate
                    highlight: menuHighlight
                    highlightFollowsCurrentItem: false
                    cellWidth : 120
                    cellHeight : 80
                    clip: true
                    focus: true
                    visible: viewHighlight


                    Keys.onReturnPressed: {
                        if (!event.isAutoRepeat) {
                            sstatscreen.enterPressed(menu.currentIndex)
                            console.log("menu.currentIndex = "+menu.currentIndex)
                            event.accepted = true
                        }
                    }

                    Component.onCompleted: {
                    						 positionViewAtIndex(currentIndex, ListView.Contain)
                                             console.log("menucount="+menu.count)
                                             console.log("menu.currentItem.width="+ menu.currentItem.width)
                                             console.log("menu.currentItem.width="+ menu.currentItem.height)
                    						
                    						} 
                    
            } // endof GridView

             /*
               Text to display if no elements are present in the list.
               This can be overridden by setting the top-level errorText property alias.
             */
             Text {
                  id: errorText
                  //anchors.centerIn: parent
                  text: "No list elements!"
                  color: "white"
                  font.pixelSize: 20
                  visible: menu.count == 0
                  wrapMode: Text.WordWrap
                  width: parent.width
                }

             /* Component 1: Delegate Component */
             Component {
                  id: menuDelegate

                  Item {
                        id: wrapper
                        width:menu.cellWidth - 20;
                        height:menu.cellHeight -13
                        //width: 130;
                        //height:  menuText.height + 65;
                        x: 15
                        y: 35

                        //Each List View Item
                        QMLTextButton {
                                          id: qmltextButton
                                          radius: 10
                                          opacity: 0.8
                                          visible: viewHighlight
                                          height: menu.cellHeight/4 + 50 // menuText.height + 65
                                          width: 110// menu.cellWidth/2 //70 //100// 130
                                          buttonLabel: name
                                          buttonLabelSize: textfontSize //16
                                          buttonColor: buttonFillColor
                                          borderColor: buttonBorderColor

                                          gradient: Gradient {
                                                  GradientStop { position: 0.0; color: Qt.lighter(buttonFillColor,1.25) }
                                                  GradientStop { position: 0.67; color: Qt.darker(buttonFillColor,1.3) }
                                              }
                         } //eof QMLTextButton

                  } //end of iner iner item

                  //make delegate to jump outside grid to arrowbuttons
                 /*
                  states: [
                           State {
                           when: menu.currentIndex == (menu.count - 1)&&(menu.currentIndex != 0)
                           PropertyChanges { target: menuDelegate }
                           //; x:rightarrowB.x; y:rightarrowB.y; width: rightarrowB.width; height: rightarrowB.height }
                                           }
                           ]
                */
               } // end of Component 1

               // Compoent 2: highlight component
               Component {
                        id: menuHighlight
                        Rectangle {
                             color: "darkblue"
                             radius: 10
                             smooth: true; clip: true
                             x: menu.currentItem.x
                             y: menu.currentItem.y + 2
                             width: 110// menu.cellWidth - 20;
                             height: menu.cellHeight -13
                             visible: viewHighlight

                            /* states: [
                                      State {
                                      when: menu.currentIndex == (menu.count - 1)&&(menu.currentIndex != 0)
                                      PropertyChanges { target: menuDelegate }

                                      //; x:rightarrowB.x;  y:rightarrowB.y; width: rightarrowB.width; height: rightarrowB.height }
                                                      }
                                      ]
                             */

                            /* Rectangle {
                                        anchors { right: parent.right; rightMargin: 5; }
                                        width: 25; height: parent.height
                                        color: parent.color
                                        Image {
                                              id: arrowImage
                                              anchors.centerIn: parent
                                              source: "qrc:/images/arrows.png"
                                              }

                                        states: [
                                                 State {
                                                 when: (menu.currentIndex == 0)&&(menu.currentIndex != (menu.count - 1))
                                                 PropertyChanges { target: arrowImage; source: "qrc:/images/arrow_down.png"; }
                                                                 },
                                                 State {
                                                 when: menu.currentIndex == (menu.count - 1)&&(menu.currentIndex != 0)
                                                 PropertyChanges { target: arrowImage; source: "qrc:/images/arrow_up.png"; }
                                                                 }
                                                 ]
                                       } */
                         }

               } // end of Component 2

           }//end of Item 2

    }//endof item 1
            
            OPLSoftkeysWithIcons {
                id: softkeys
                //anchors.bottom: menu.bottom
                anchors.top: parent.bottom
                anchors.topMargin: 5
                anchors.rightMargin: 10
                anchors.leftMargin: 10
				//TODO : make this as enabel or disable to hide
               // softkeyIconList: ["", "", "", "qrc:/images/help-icon.png"]
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
                        sstatscreen.goBack();
                        }
                        break;
                    case Qt.Key_F2:
                        {
                        // Use F2 for now but we really have to use enterPressed()
                        sstatscreen.source ="qrc:/qml/SystStatSecondPageScreen.qml"
                        event.accepted = true
                        }
                        break;
                    case Qt.Key_F3:
                        {
                         sstatscreen.goBack();
                       }
                        break;
                    case Qt.Key_F4:
                        {
                         sstatscreen.goBack();
                        }
                        break;
                }  // endof switch
            } //endof if

            event.accepted = true
        } // endof keys.onPressed

    } // end of Rectangle_1
}// endof Main Rectangle
