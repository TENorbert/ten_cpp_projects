/************************************************************
** TextAndImagebuttonutton
** Use for Adding(Active) Buttons to Screens
** Note: Make Sure you put
**       "QMLTextButton ./<path>QMLTextButton.qml"
**       or in your qmldir text file 
**       which is here /armoebuild/users/tambeno/DSE/linux/Condor/UI/ecolab-qt-components/qml/qmldir
**    
**
** Usage: eg QMLTextButton {} // creates a simple Button
**
** Or Simply create a Button as: QMLTextButton {}
** Property of ECOLAB RD&E Department, Dec 09th 2015
** Author: Norbert Tambe E.
*************************************************************/

import QtQuick 1.0

Rectangle {
       id: qmltextButton
       smooth: true; radius: 5; z: 10; //opacity: 0.6
       visible: true
       width: 130; height: mainText.height
       border {color: onKeyedColor; width: 2}

       //these properties act as constants, useable outside this QML file
       property int buttonHeight: mainText.height
       property int buttonWidth:  130

       property string buttonLabel
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

       Text {
             id: mainText
             font.pixelSize: 20
             anchors.verticalCenter: parent.verticalCenter
             anchors.horizontalCenter: parent.horizontalCenter
             text: buttonLabel
             color: "white"
             //font.family : screenfont
             font.bold : dobold
             font.family: "helvetica"
             wrapMode: Text.WordWrap
                       
            }
  }


