/************************************************************
** TextAndImagebuttonutton
** Use for Adding(Active) Buttons to Screens
** Note: Make Sure you put
**       "Button ./<path>TextAndImageButton.qml"
**       or in your qmldir text file 
**       which is here /armoebuild/users/tambeno/DSE/linux/Condor/UI/ecolab-qt-components/qml/qmldir
**    
**
** Usage: eg TextAndImageButton {} // creates a simple Button
**
** Or Simply create a Button as: TextAndImageButton {}
** Property of ECOLAB RD&E Department, Dec 09th 2015
** Author: Norbert Tambe E.
*************************************************************/

import QtQuick 1.0

Rectangle {
       id: textImageButton
       smooth: true; radius: 5; z: 10; opacity: 0.6
       visible: true
       width: 130; height: mainText.height
       border {color: "#B9C5D0"; width: 2}

       //these properties act as constants, useable outside this QML file
       property int buttonHeight: mainText.height
       property int buttonWidth:  130

       property string buttonLabel
       property string buttonImage: "moon.png"
       property color buttonColor: "darkblue"

       property real buttonLabelSize: 16
       property bool dobold: false

       //the color highlight when the mouse hovers on the rectangle
       property color onKeyedColor: "lightsteelblue"
       property color borderColor: "transparent"

       //Button Signal
       signal buttonPressed()  // for pressing Button
       

       gradient: Gradient {
           GradientStop {color: "#CFF7FF"; position: 0.0}
           GradientStop {color: "#99C0E5"; position: 0.57}
           GradientStop {color: "#719FCB"; position: 0.9}
       }

       Item {
           id: bItem
           anchors.centerIn: parent
           anchors.fill: parent
           
           Column {
                   width : myImage.width + 25
                   spacing: 5
                               
                   Text {
                      id: dummy
                      font.pixelSize: 1
                      anchors.horizontalCenter: parent.horizontalCenter
                      text: " "
                      color: "white"
                      font.family : "helvetica" //screenfont
                      font.bold : dobold
                   }
                   Image {
                      id: myImage
                      width: 80 //parent.width/2
                      height: 40 // parent.height
                      smooth: true
                      //anchors.centerIn: parent
                      anchors.horizontalCenter: parent.horizontalCenter
                      source: buttonImage
                   }
                   Text{
                     id: mainText
                     anchors.bottom: parent.bottom
                     //anchors.centerIn: parent
                     anchors.horizontalCenter: parent.horizontalCenter
                     font.pixelSize: 16
                     text: buttonLabel
                     color: "white"
                     font.bold: dobold
                     font.family : "helvetica"
                   }
           }
        }

        //Change B scale and color when Enter Key is pressed
        //Keys.onEnterPressed: console.log("Pressed Enter");
         scale: Keys.onEnterPressed ? 1.1 : 1.00
         //Animate the scale property change
         Behavior on scale { NumberAnimation{ duration: 55 } }
         color: Keys.onEnterPressed ? Qt.darker(buttonColor, 1.5) : buttonColor
         //animate the color whenever the color property changes
         Behavior on color { ColorAnimation{ duration: 55 } }


          // Button Interactive properties
         Item {
               id: buttonkeyHandler
               anchors.fill: parent
               smooth: true
               focus: true
               // border color removed out of focus
               Keys.onReleased: { parent.border.color = borderColor }

               Keys.onPressed: {
               //border color displayed of focus key
               parent.border.color = onKeyedColor
               buttonPressed()
               if (event.key == Qt.Key_Enter) {
               color = "lighsteelblue";
               //event.accepted = true;
               //Can call to do somthing function or javascript
               //callAfucntion();
               }
             }

         }

 }
