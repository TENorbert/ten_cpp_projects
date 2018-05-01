//%****************************************
//%
//% Column Of Text
//%
//%***************************************

import QtQuick 1.0

Item {
     id: columnTextContainer
     anchors.fill: parent
     
     //Properties exported outside
     property string  textOneTitle      : "Temperature"
     property string  textOneData       : "0 F"
     property string  textTwoTitle      : "Conductivity"
     property string  textTwoData       : "0 uS/cm"
     property string  textThreeTitle    : "Water Pressure Switch Status"
     property string  textThreeData     : "CLOSE"
     property string  textFourTitle     : "Valve State"
     property string  textFourData      : "CLOSE"
     property string  textFiveTitle     : "Timer"
     property string  textFiveData      : "0 s"
     property string  textSixTitle      : "Valve Test"
     property string  textSixData       : "NONE"


     property real     textWidth        : 360
     property real     textHeight       : 26
     property real     textdataWidth    : 200
     property color  textFillColor      : "#0082c8"
     property color  textColor          : "white"
     property string  textFont          : "helvetica"
     property int     textFontSize      : 16
     property bool    textBold          : false
 

     Column {
             id: columnOne
             spacing : 3
             anchors { fill: parent; margins: 5}
             visible : true
     	     
             Rectangle {
                       id: textOne
                       width: parent.width; height: text1Title.height
                       color: textFillColor
                       radius: 8
                       border.width: 1
                       gradient: Gradient {
                                           GradientStop { position: 0.0; color: "#0082c8" }
                                          //GradientStop { position: 1.0; color: "transparent" }
                                 }
                       /*
       	     		//% Image as background
       	     		Image {
             	   		id: img
	      	  		width: textOne.width; height: textOne.height
                   		source:"qrc:/images/ngc/Display2x4ButtonOut.png"
                   		anchors.fill: parent
             	   		smooth: true
	           		fillMode: Image.Stretch
	           		//fillMode: Image.PreserveAspectCrop
      	    		}
                      */

       
                      
                       Text {
                             id: text1Title
                             width: textWidth; height:textHeight //width: text.width; height: text.height
                             anchors{verticalCenter: textOne.verticalCenter; left: textOne.left; leftMargin:2 }
                             text: textOneTitle
                             color: textColor
                             font.bold: textBold
                             font.pointSize: textFontSize
                             font.family: textFont
                             wrapMode: Text.Wrap
		       }
                       Text {
                             id: text1Data
                             width: textdataWidth ; height:textHeight //width: text.width; height: text.height
                             anchors{verticalCenter: textOne.verticalCenter;
                                     left: text1Title.right; leftMargin: 5
                                     right: textOne.right; rightMargin:2 }
                             text: textOneData
                             color: textColor
                             font.bold: textBold
                             font.pointSize: textFontSize
                             font.family: textFont
                             wrapMode: Text.Wrap
		       }

	     }

             Rectangle {
                       id: textTwo
                       width: parent.width; height: text2Title.height
                       color: textFillColor
                       radius: 8
                       border.width: 1
                       gradient: Gradient {
                                           GradientStop { position: 0.0; color: "#0082c8" }
                                          //GradientStop { position: 1.0; color: "transparent" }
                                 }
                      
                       Text {
                             id: text2Title
                             width: textWidth ; height:textHeight //width: text.width; height: text.height
                             anchors{verticalCenter: textTwo.verticalCenter; left: textTwo.left; leftMargin:2 }
                             text: textTwoTitle
                             color: textColor
                             font.bold: textBold
                             font.pointSize: textFontSize
                             font.family: textFont
                             wrapMode: Text.Wrap
		       }
                       Text {
                             id: text2Data
                             width: textdataWidth; height:textHeight //width: text.width; height: text.height
                             anchors{verticalCenter: textTwo.verticalCenter;
                                     left: text2Title.right; leftMargin: 5;
                                     right: textTwo.right; rightMargin:2 }
                             text: textTwoData
                             color: textColor
                             font.bold: textBold
                             font.pointSize: textFontSize
                             font.family: textFont
                             wrapMode: Text.Wrap
		       }

	     }
             
	     Rectangle {
                       id: textThree
                       width: parent.width; height: text3Title.height
                       color: textFillColor
                       radius: 8
                       border.width: 1
                       gradient: Gradient {
                                           GradientStop { position: 0.0; color: "#0082c8" }
                                          //GradientStop { position: 1.0; color: "transparent" }
                                 }
                      
                       Text {
                             id: text3Title
                             width: textWidth; height:textHeight //width: text.width; height: text.height
                             anchors{verticalCenter: textThree.verticalCenter; left:textThree.left; leftMargin:2 }
                             text: textThreeTitle
                             color: textColor
                             font.bold: textBold
                             font.pointSize: textFontSize
                             font.family: textFont
                             wrapMode: Text.Wrap
		       }
                       Text {
                             id: text3Data
                             width: textdataWidth; height:textHeight //width: text.width; height: text.height
                             anchors{verticalCenter: textThree.verticalCenter;
                                     left: text3Title.right; leftMargin: 5;
                                     right: textThree.right; rightMargin:2 }
                             text: textThreeData
                             color: textColor
                             font.bold: textBold
                             font.pointSize: textFontSize
                             font.family: textFont
                             wrapMode: Text.Wrap
		       }

	     }
         Rectangle {
                       id: textFour
                       width: parent.width; height: text4Title.height
                       color: textFillColor
                       radius: 8
                       border.width: 1
                       gradient: Gradient {
                                           GradientStop { position: 0.0; color: "#0082c8" }
                                          //GradientStop { position: 1.0; color: "transparent" }
                                 }

                       Text {
                             id: text4Title
                             width: textWidth; height:textHeight //width: text.width; height: text.height
                             anchors{verticalCenter: textFour.verticalCenter; left:textFour.left; leftMargin:2 }
                             text: textFourTitle
                             color: textColor
                             font.bold: textBold
                             font.pointSize: textFontSize
                             font.family: textFont
                             wrapMode: Text.Wrap
               }
                       Text {
                             id: text4Data
                             width: textdataWidth; height:textHeight //width: text.width; height: text.height
                             anchors{verticalCenter: textFour.verticalCenter;
                                     left: text4Title.right; leftMargin: 5;
                                     right: textFour.right; rightMargin:2 }
                             text: textFourData
                             color: textColor
                             font.bold: textBold
                             font.pointSize: textFontSize
                             font.family: textFont
                             wrapMode: Text.Wrap
               }

         }
         Rectangle {
                       id: textFive
                       width: parent.width; height: text5Title.height
                       color: textFillColor
                       radius: 8
                       border.width: 1
                       gradient: Gradient {
                                           GradientStop { position: 0.0; color: "#0082c8" }
                                          //GradientStop { position: 1.0; color: "transparent" }
                                 }

                       Text {
                             id: text5Title
                             width: textWidth; height:textHeight //width: text.width; height: text.height
                             anchors{verticalCenter: textFive.verticalCenter; left:textFive.left; leftMargin:2 }
                             text: textFiveTitle
                             color: textColor
                             font.bold: textBold
                             font.pointSize: textFontSize
                             font.family: textFont
                             wrapMode: Text.Wrap
               }
                       Text {
                             id: text5Data
                             width: textdataWidth; height:textHeight //width: text.width; height: text.height
                             anchors{verticalCenter: textFive.verticalCenter;
                                     left: text5Title.right; leftMargin: 5;
                                     right: textFive.right; rightMargin:2 }
                             text: textFiveData
                             color: textColor
                             font.bold: textBold
                             font.pointSize: textFontSize
                             font.family: textFont
                             wrapMode: Text.Wrap
               }

         }
         Rectangle {
                       id: textSix
                       width: parent.width; height: text6Title.height
                       color: textFillColor
                       radius: 8
                       border.width: 1
                       gradient: Gradient {
                                           GradientStop { position: 0.0; color: "#0082c8" }
                                          //GradientStop { position: 1.0; color: "transparent" }
                                 }


                       Text {
                             id: text6Title
                             width: textWidth; height:textHeight //width: text.width; height: text.height
                             anchors{verticalCenter: textSix.verticalCenter; left:textSix.left; leftMargin:2 }
                             text: textSixTitle
                             color: textColor
                             font.bold: textBold
                             font.pointSize: textFontSize
                             font.family: textFont
                             wrapMode: Text.Wrap
               }
                       Text {
                             id: text6Data
                             width: textdataWidth; height:textHeight //width: text.width; height: text.height
                             anchors{verticalCenter: textSix.verticalCenter;
                                     left: text6Title.right; leftMargin: 5;
                                     right: textSix.right; rightMargin:2 }
                             text: textSixData
                             color: textColor
                             font.bold: textBold
                             font.pointSize: textFontSize
                             font.family: textFont
                             wrapMode: Text.Wrap
               }

         }




     } //end of Col


}
