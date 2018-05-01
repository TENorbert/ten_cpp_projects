/***********************************************************************
**
** SSMainScreen.qml    //testing
**
************************************************************************/
import Qt 4.7
import QtQuick 1.0
import com.ecolab.components 1.0
//import GarfunkelResourceStrings 0.1
import "../views"

SystemStatusMainView
{
            id: mSSScreen
            breadcrumb:  "System Status" 
            //softKeyIconList: ["qrc:/images/home.png", "qrc:/images/back-icon.png", "qrc:/images/status.png", "qrc:/images/help-icon.png" ]
            //softKeyIconList: ["qrc:/images/home.png", "qrc:/images/select-formula.png", "qrc:/images/laundry-load-counts-1.png", "qrc:/images/status.png"]
            softKeyIconList: ["qrc:/images/ngc/HomeOut.png", "qrc:/images/ngc/BackOut.png", "qrc:/images/ngc/BlankButtonOut.png", "qrc:/images/ngc/HelpOut.png"]
            //rbImage: "qrc:/images/right_arrow.png"
            arrowImage: "qrc:/images/condor/leftBlueArrow.png"


            menuModel: ListModel
                {
                    ListElement { name: "Display ";       qmlFile: "Screen.qml" }
                    ListElement { name: "MakeDown";      qmlFile: "qml/Help.qml" }
                    ListElement { name: "Product Refill";       qmlFile: "qml/Help.qml" }
                    ListElement { name: "B.WaterCall";     qmlFile: "qml/Help.qml" }
                    ListElement { name: "Alarm Status";       qmlFile: "qml/Help.qml" }
                    ListElement { name: "Actions";      qmlFile: "qml/Help.qml" }
                    //ListElement { name: "View System Info"; qmlFile: "qml/Help.qml" }
                }

            property variant qmlList: [
                    "qrc:/qml/systemStatus/Screen.qml",
                    "qrc:/qml//Help.qml",
                    "qrc:/qml//Help.qml",
                    "qrc:/qml//Help.qml",
                    "qrc:/qml//Help.qml",
                    "qrc:/qml//Help.qml"
            ]


            onEnterPressed:
            {
              mSSScreen.source = qmlList[currentIndex]
              console.log("Wow CurrentIdex = " + currentIndex + " Entered")
            }



             Component.onCompleted: {

                //Call a functions once Instance is created!!
                }

            Component.onDestruction:  {
               mainView: activeFocus ? console.log("I Have Active Focus") : console.log("I don't have Active Focus")
                // mainView.state = ""

            }

            Keys.onPressed: {
                // disable auto repeat
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
                         //back to Main Menu Screen if F1-F3-F4 pressed //
                        case Qt.Key_F1:
                            {
                                event.accepted = true;
                                console.log("F1: Welcome Home!!");
                                mSSScreen.source ="qrc:/qml//MainScreen.qml"
                            }
                            break;
                        case Qt.Key_F2:
                            {
                                event.accepted = true
                                console.log("F2: Back to Home!!");
                                mSSScreen.visible = false;
                                mSSScreen.focus   = false;
                                mSSScreen.goBack();
                            }
                            break;
                        case Qt.Key_F3:
                            {
                                //event.accepted = true
                                //mSSScreen.goBack(); // Status but just go back for now!!
                           }
                            break;
                        case Qt.Key_F4:
                            {
                                event.accepted = true
                                mSSScreen.source ="qrc:/qml//Help.qml"                               
                            }
                            break;
                       }
                  }

            }


} // eof mSSScreen

