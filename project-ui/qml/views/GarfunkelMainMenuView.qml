import QtQuick 1.0
import com.ecolab.components 1.0

Rectangle {
    id: screen
    anchors.fill: parent
    width: 480
    height: 272

    default property alias content: main.children

    property alias breadcrumb: breadcrumb.text
    //property string pagetitlebreadcrumbText

/*    property alias softKeyIconList: softkeys.softkeyIconList
    property alias btnIcon1: softkeys.btnIcon1
    property alias btnIcon2: softkeys.btnIcon2
    property alias btnIcon3: softkeys.btnIcon3
    property alias btnIcon4: softkeys.btnIcon4 */
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
    property string screenfont:  "helvetica" // (isTMScreen==true)? AquanomicsLM.GetTMLangaugeFontName() : AquanomicsLM.GetPrimaryLangaugeFontName()
    property variant brdcrumbfont : (setEntireScreenSameFont==true) ?  screenfont : "helvetica"
    property bool fontBold : false //(isTMScreen==true)? AquanomicsLM.GetTMLangaugeFontBoldStatus() : false
    
    property bool menuHighlightVisible : true

    property color buttonFillColor: "#0082c8"
    property color buttonBorderColor: "#7A8182"

    property color buttonHighlightColor: "darkblue"

    property real buttonlabelSize: 16

    signal goBack()
    signal enterPressed(int currentIndex)
    focus: true


    function reloadFontProperties()
    {
        //console.log("************Inside reloadFontProperties*******");
        
        screen.screenfont = "helvetica"  //(isTMScreen==true)? AquanomicsLM.GetTMLangaugeFontName() : AquanomicsLM.GetTMLangaugeFontName()
       
        screen.fontBold = false //(isTMScreen==true)? AquanomicsLM.GetTMLangaugeFontBoldStatus() : false
        brdcrumbfont =  (setEntireScreenSameFont==true) ? screenfont: "helvetica"
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

/*
    // Main Page Title View
    TitleOPLBreadcrumb{
        id: pagetitle
        anchors.fill: parent
        width:  parent.width; height: parent.height/10
        text: pagetitlebreadcrumbText
        //anchors.top: parent.top
        anchors.topMargin: 2
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: - 73;

        breadcrumbfont :  brdcrumbfont
        breadcrumbfontbold : fontBold

    }
*/

    Rectangle {
        id: menuView
        anchors.fill: parent
        color: "steelblue"

        /* Item 1 */
        Item {
            id: container
            anchors { fill: parent; margins: 10; }

            OPLBreadcrumb {
                id: breadcrumb
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                width:  parent.width
                breadcrumbfont :  brdcrumbfont
                breadcrumbfontbold : fontBold
                text : "hereeeee"
            }

          /* Item  embedded in an item */
          Item {
            id: main
            width: parent.width
            anchors { left: parent.left; right: parent.right;  }
            anchors.top: breadcrumb.bottom
            anchors.topMargin: (breadcrumb.text == "" ? 15 : 10)
            anchors.leftMargin: 10
            anchors.bottom :  (softkeysEnabled== true ? softkeys.top : parent.bottom)
            anchors.bottomMargin: (breadcrumb.text == "" ? 10 : 9) //(footerinfo.text == "" ? 1 : (headerinfo.text == "") ? 5: 9)


           /* The menu */
            GridView {
                    id: menu
                    anchors { fill: parent; }
                    delegate: menuDelegate
                    highlight: menuHighlight
                    highlightFollowsCurrentItem: false
                    cellWidth : 150
                    cellHeight : 100
                    clip: true
                    focus: true
                    visible: viewHighlight


					
                    Keys.onReturnPressed: {
                        if (!event.isAutoRepeat) {
                            screen.enterPressed(menu.currentIndex)
                            console.log("menu.currentIndex"+menu.currentIndex + "Displayed")
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
                        width:menu.cellWidth - 20; height:menu.cellHeight -13
                        //width: 130;
                        //height:  menuText.height + 65;
                        x: 10
                        y: 10

                       //Each List View Item
                        TextAndImageButton {
                                    id: textandImageButton
                                    radius: 10
                                    opacity: 0.8
                                    visible: viewHighlight
                                    height: menu.cellHeight/4 + 65 // menuText.height + 65
                                    width: 130
                                    buttonLabel: name
                                    buttonLabelSize: buttonlabelSize //16
                                    buttonImage: symbol
                                    buttonColor: buttonFillColor
                                    borderColor: buttonBorderColor

                                    gradient: Gradient {
                                            GradientStop { position: 0.0; color: Qt.lighter(buttonFillColor,1.25) }
                                            GradientStop { position: 0.67; color: Qt.darker(buttonFillColor,1.3) }
                                        }
                                }

                        /*
                        //each ListItem of ListView?
                        Rectangle {
                        color: "darkblue" //"lightsteelblue"
                        radius: 10
                        opacity: 0.6;
                        //anchors.horizontalCenter: parent.horizontalCenter
                        //z: -1
                        width: 130;
                        height:  menuText.height + 65;
                        visible : viewHighlight

                           Column {
                               anchors.fill: parent
                               spacing : 5
                               width : imageSymbol.width + 25
                               Text {
                                  id: dummy
                                  font.pixelSize: 1
                                  anchors.horizontalCenter: parent.horizontalCenter
                                  text: " "
                                  color: "white"
                                  font.family : "helvetica" //screenfont
                                  font.bold : false //fontBold
                                  } // Items with more than one text

                               Image {
                                  id: imageSymbol
                                  anchors.horizontalCenter: parent.horizontalCenter
                                  source: symbol
                                  width: 80
                                  height : 40
                                  }

                               Text {
                                  id: menuText
                                  font.pixelSize: 16
                                  anchors.horizontalCenter: parent.horizontalCenter
                                  text: name
                                  color: "white"
                                  font.family : "helvetica" //screenfont
                                  font.bold : false //fontBold
                                  }
                           } // column ends
                         } // end of iner iner Rectangle
                         */
                  } //end of iner iner item
                   
             } // end of Component 1

              // Compoent 2: highlight component
               Component {
                        id: menuHighlight			
                        Rectangle {
                             color: "darkblue"
                             radius: 10
                             smooth: true; clip: true
                             x: menu.currentItem.x
                             y: menu.currentItem.y
                             width: menu.cellWidth - 20; height: menu.cellHeight - 11
                             visible: viewHighlight


                             gradient: Gradient {
                                     GradientStop { position: 0.0; color: Qt.lighter(buttonHighlightColor,1.25) }
                                     GradientStop { position: 0.67; color: Qt.darker(buttonHighlightColor,1.3) }
                                 }
                        }

               } // end of Component 2

            }//end of Item 2

           }//endof item 1



        focus: true
        Keys.forwardTo: [parent, menu]
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
                    	{
                        screen.goBack();
                        }
                        break;
                    case Qt.Key_F2:
                        break;
                    case Qt.Key_F3:
                        // testing: For now call System Status from here!!
                        console.log( "Back To Main Menu Screen" )
                        screen.source ="qrc:/qml//GarfunkelSystemStatusIdleScreen.qml"
                        break;

                    case Qt.Key_F4:
                        {
                            screen.source ="qrc:/qml//Help.qml"
                            event.accepted = true
                        }
                        break;

               }  // endof switch
            } //endof if

            event.accepted = true
        } // endof keys.onPressed

      }//% MenuView rec ends

} // endof Main Rectangle
