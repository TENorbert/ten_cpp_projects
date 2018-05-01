import QtQuick 1.0
import com.ecolab.components 1.0
//import AquanomicsResourceStrings 0.1
import "../views" //% additional Components

 FocusScope {
    property alias interactive: gridView.interactive
    //% Buttons Properties
    property color buttonFillColor: "#0082c8"
    property color buttonBorderColor: "#7A8182"
    property color buttonHighlightColor: "darkblue"
    property real textfontSize: 16
    property alias model: gridView.model
    property alias cellWidth: gridView.cellWidth
    property alias cellHeight: gridView.cellHeight
    property alias delegate: gridView.delegate
    property alias highlight: gridView.highlight
    property alias currentIndex: gridView.currentIndex
  

     onActiveFocusChanged: {
         if (activeFocus)
             mainView.state = ""
     }

     Rectangle {
         id: gridholder
         anchors {fill: parent } // bottom: parent.bottom; bottomMargin: 5}
         width: GridView.cellWidth*3  ; height: GridView.cellHeight*2 - 20
         clip: true
         //border.width: 2
         color: "lightsteelblue"
         //gradient: Gradient {
         //                    GradientStop { position: 0.0; color: Qt.lighter(buttonFillColor,1.25) }
         //                    GradientStop { position: 0.67; color: Qt.darker(buttonFillColor,1.3) }
         //                   }

         GridView {
             id: gridView
             currentIndex: 0; //% gridView always starts with first index
             anchors { fill: parent
                        topMargin: 2
                     } 
             cellWidth: 153 ; cellHeight: 100 //152
             focus: true
             //model: 12
 	     flow: GridView.TopToBottom //%View from Top to Bottom
 	     //flow: GridView.LeftToRight //%View from Left to Right
             //snapMode: GridView.SnapOneRow
             
             highlightFollowsCurrentItem: false //%decides if highlight is done by GridView or highlight
             delegate: Item {
                 id: mydelegate
                 width: gridView.cellWidth; height: gridView.cellHeight
                 Rectangle {
                     id: content
                     color: "transparent"
                     smooth: true
                     anchors.fill: parent; anchors.margins: 5; radius: 15
                      
		     //Each List View Item
                      TextAndImageButton {
                                    radius: 15
                                    //opacity: 0.8
                                    anchors{ fill: parent; margins: 3 }
                                    
                                    buttonLabel: name
                                    buttonLabelSize:  textfontSize //16
                                    buttonImage: symbol
                                    buttonColor: buttonFillColor
                                    borderColor: buttonBorderColor

                      }
 

                }

                 MouseArea {
                     id: mouseArea
                     anchors.fill: parent

                     onClicked: {
                         gridView.currentIndex = index
                         mydelegate.forceActiveFocus()
                     }
                 }

                 states: State {
                     name: "active"; when: mydelegate.activeFocus
                     PropertyChanges { target: content; color: buttonHighlightColor; scale: 1.05 }
                 }

                 transitions: Transition {
                     NumberAnimation { properties: "scale"; duration: 100 }
                 }
              } //% end of Delegate Item
 
              highlight: Item {
                         id: itemHighlight
                         width: gridView.cellWidth; height: gridView.cellHeight
 
                	 Rectangle {
                     	     id: myhighlight
                    	     color: "transparent"
                     	     smooth: true
                     	     anchors.fill: parent; anchors.margins: 5; radius: 15

                             Rectangle {
                                     color: buttonHighlightColor
                             	     radius: 15
                              	     smooth: true; clip: true
                                     x: gridView.currentItem.x + 1
                                     y: gridView.currentItem.y + 2
                                     width: gridView.cellWidth -15 //- 20; // use gridView.width
                                     height: gridView.cellHeight -15
                                     visible: true

                             } 
                        }    
                    
                     MouseArea {
                     id: mouseArea
                     anchors.fill: parent

                     onClicked: {
                         gridView.currentIndex = index
                         itemHighlight.forceActiveFocus()
                       }
                    }

                 states: State {
                     name: "highlightActive"; when: itemHighlight.activeFocus
                     PropertyChanges { target: myhighlight; color: "transparent"; scale: 1.05 }
                 }

                 transitions: Transition {
                     NumberAnimation { properties: "scale"; duration: 100 }
                 }
                   
            
              }//% end of highlight
             
              Component.onCompleted: {
                                      positionViewAtIndex(currentIndex, ListView.Contain)
                                      console.log("GridView.count = "+ gridView.count)
                                      console.log("GridView.currentItem.width= "+ gridView.currentItem.width)
                                      console.log("GridView.currentItem.height= "+ gridView.currentItem.height)
                                     } 

           }//% eof Grid View
     }//% Eof Rec
 }//% EOf FocusScope
