/***********************************************************************
**
** DMainScreen.qml  
**
************************************************************************/
import Qt 4.7
import QtQuick 1.0
import com.ecolab.components 1.0
//import GarfunkelResourceStrings 0.1
import "../views"

DiagnosticsView
{
    id: mDScreen
    breadcrumb:  "Diagnostics" //customerInfoData.customerName

    //softKeyIconList: ["qrc:/images/home.png", "qrc:/images/back-icon.png", "qrc:/images/on.png", "qrc:/images/help-icon.png"]

    arrowImage: "qrc:/images/condor/leftBlueArrow.png"


    menuModel: ListModel
        {
            ListElement { name: "Valves";       qmlFile: "Diagnostics.qml" }
            ListElement { name: "Status";       qmlFile: "qml/Help.qml" }
            ListElement { name: "IO Boards";      qmlFile: "qml/Help.qml" }
            ListElement { name: "Pumps";       qmlFile: "qml/Help.qml" }
            ListElement { name: "GarfunKel";     qmlFile: "qml/Help.qml" }
            ListElement { name: "Condor";      qmlFile: "CondorScreen.qml" }
        }

    property variant qmlList: [
            "qrc:/qml/diagnostics/VMainScreen.qml",
            "qrc:/qml//Help.qml",
            "qrc:/qml//Help.qml",
            "qrc:/qml//Help.qml",
            "qrc:/qml//Help.qml",
            "qrc:/qml//diagnostics/CondorScreen.qml"
    ]


    onEnterPressed:
    {
      mDScreen.source = qmlList[currentIndex]
      console.log("Wow CurrentIdex = " + currentIndex + " Entered")
    }




     Component.onCompleted: {
 
    //call choice fxn once instatiation is completed!
    }


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
                 //back to Main Menu Screen if F1-F3-F4 pressed //
                case Qt.Key_F1:
                    {
                       event.accepted = true
                       if(f1Enabled)
                       {
                           //Disabling Diagnostics Mode
                            console.log("Going To Main Menu, Disabling Diagnostics: F1");
                            diagcontext.diagnosticsTestRequest = false;
                            console.log("To Main Menu key: F1");
                            mDScreen.source ="qrc:/qml//MainScreen.qml"
                       }
                    }
                    break;
                case Qt.Key_F2:
                    {
                      event.accepted = true
                      if(f2Enabled)
                      {
                          //Back or CANCEL Diagnostics Mode
                           console.log("Going Back, Disabling Diagnostics: F2");
                           diagcontext.diagnosticsTestRequest = false;
                           console.log("Back To Main Menu key: F2");
                           mDScreen.visible = false;
                           mDScreen.focus = false;
                           mDScreen.goBack();
                      }
                    }
                    break;
                case Qt.Key_F3:
                    {
                       event.accepted = true
                       if(f3Enabled)
                       {
                            //event.accepted = true
                        }
                   }
                    break;
                case Qt.Key_F4:
                    {
                        event.accepted = true
                        if(f4Enabled)
                        {
                           console.log("Help Key : F4");
                           mDScreen.source ="qrc:/qml//Help.qml";
                         }

                    }
                    break;
            }
        }

    } // endof keys.onPressed




    
} // eof mDScreen

