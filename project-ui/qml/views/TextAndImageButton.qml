/************************************************************
** TextAndImageButton
** Use for Adding(Active) Buttons to Screens
** Note: import "views" and add 
**       "TextAndImageButton.qml" in .qrc file
**    
** Usage: eg TextAndImageButton {} // creates a simple Button
**
** Or Simply create a Button as: TextAndImageButton {}
** Dec 09th 2015
** Author: Norbert Tambe E.
*************************************************************/

import QtQuick 1.0

Rectangle {
       id: textImageButton
       smooth: true; radius: 5; z: 10; //opacity: 0.6
       visible: true
       width: 153; height: 100 //mainText.height
       border {color: onKeyedColor; width: 2}

       //these properties act as constants, useable outside this QML file
       property int buttonHeight: mainText.height
       property int buttonWidth:  153

       property string buttonLabel
       property string buttonImage: "moon.png"
       property color buttonColor: "darkblue"

       property real buttonLabelSize: 16
       property bool dobold: false

       //the color highlight when the mouse hovers on the rectangle
       property color onKeyedColor: "lightsteelblue"
       property color borderColor: "transparent"

       //% Image as background 
       Image {
              id: img
	      width: parent.width; height: parent.height
              source:"qrc:/images/ngc/SixBigButtonOut.png"
              anchors.fill: parent
              smooth: true
	      fillMode: Image.Stretch
	      //fillMode: Image.PreserveAspectCrop
       }

       

       //gradient: Gradient {
       //    GradientStop {color: "#CFF7FF"; position: 0.0}
       //    GradientStop {color: "#99C0E5"; position: 0.57}
       //    GradientStop {color: "#719FCB"; position: 0.9}
       // }
       gradient: Gradient {
           GradientStop {color: buttonColor; position: 0.0}
           GradientStop {color: buttonColor; position: 0.57}
           GradientStop {color: buttonColor; position: 0.9}
       }

       Item {
           id: bItem
           anchors.centerIn: parent
           anchors.fill: parent



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
              width: 80
              height: 40
              smooth: true
              anchors.horizontalCenter: parent.horizontalCenter
              anchors.top: parent.top; anchors.topMargin: 7
              source: buttonImage
           }
           Text{
             id: mainText
             anchors.horizontalCenter: parent.horizontalCenter
             anchors.top: myImage.bottom; anchors.topMargin:5
             font.pixelSize: 16
             text: buttonLabel
             color: "white"
             font.bold: dobold
             font.family : "helvetica"
           }

        }


        MouseArea {
		 id: mArea
                 anchors.fill: parent
                 onClicked: {
                             console.log("Button Pressed");
                 }
        }

     /*
       //Change Button scale and color when Enter Key is pressed
       //Keys.onReturnPressed: console.log("Pressed Enter");

       scale: Keys.onEnterPressed ? 1.1 : 1.00
       //Animate the scale property change
       Behavior on scale { NumberAnimation{ duration: 55 } }
       color: Keys.onEnterPressed ? Qt.darker(buttonColor, 1.5) : buttonColor
       //animate the color whenever the color property changes
       Behavior on color { ColorAnimation{ duration: 55 } }

       Keys.onEnterPressed:  {border.color = borderColor }
       Keys.onReleased: {border.color = onKeyedColor}
       Keys.onRightPressed: {border.color = onKeyedColor}
       Keys.onLeftPressed: {border.color = onKeyedColor}
       Keys.onUpPressed: {border.color = onKeyedColor}
       Keys.onDownPressed: {border.color = onKeyedColor}
      */

 }
