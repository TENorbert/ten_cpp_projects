/***********************************************************************
**
** ValvesScreen.qml  
**
************************************************************************/
import Qt 4.7
import QtQuick 1.0
import com.ecolab.components 1.0
//import GarfunkelResourceStrings 0.1
import "../views"

ValvesView
{
    id: mVScreen
    breadcrumb:  "Valves" 

    //softKeyIconList: ["qrc:/images/home.png", "qrc:/images/back-icon.png", "", "qrc:/images/help-icon.png"]
    softKeyIconList: ["qrc:/images/ngc/BlankButtonOut.png" , "qrc:/images/ngc/BackOut.png", "qrc:/images/ngc/BlankButtonOut.png", "qrc:/images/ngc/BlankButtonOut.png"]
    arrowImage: "qrc:/images/condor/leftBlueArrow.png" //"qrc:/images/BlueArrow.png"


   menuModel: ListModel
            {
                ListElement { name: "S Valve";       qmlFile: "ValveOneScreen.qml" }
                ListElement { name: "P Valve";       qmlFile: "ValveTwoScreen.qml" }
                ListElement { name: "W. Inlet";      qmlFile: "ValveThreeScreen.qml" }
                ListElement { name: "O1 Valve";       qmlFile: "ValveFourScreen.qml" }
                ListElement { name: "O2 Valve";     qmlFile: "ValveFiveScreen.qml" }
                ListElement { name: "Drain V.";      qmlFile: "ValveSixScreen.qml" }
                //ListElement { name: "View System Info"; qmlFile: "qml/Help.qml" }
                //ListElement { name: "Diagnostics ";     qmlFile: "qml/Help.qml" }
            }


        property variant qmlList: [
                "qrc:/qml/diagnostics/ValveOneScreen.qml",
                "qrc:/qml/diagnostics/ValveTwoScreen.qml",
                "qrc:/qml/diagnostics/ValveThreeScreen.qml",
                "qrc:/qml/diagnostics/ValveFourScreen.qml",
                "qrc:/qml/diagnostics/ValveFiveScreen.qml",
                "qrc:/qml/diagnostics/ValveSixScreen.qml"
        ]



        onEnterPressed:
        {
          mVScreen.source = qmlList[currentIndex]
          console.log("Wow CurrentIdex = " + currentIndex + " Entered")
        }



         Component.onCompleted: {

         //Call a function here Once Instance is created!!
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
                case Qt.Key_F1:
                    {   // Back to Home!
                        event.accepted = true
                        mVScreen.source ="qrc:/qml//MainScreen.qml"
                    }
                    break;
                case Qt.Key_F2:
                    {
                        // Going Back
                        console.log("F2: Back To Diagnostics Menu")
                        event.accepted = true
                        mVScreen.visible = false;
                        mVScreen.focus = false;
                        mVScreen.goBack();

                    }
                    break;
                case Qt.Key_F3:
                    {
                       //Leave Blank for Now!!
                   }
                    break;
                case Qt.Key_F4:
                    {
                         // U should not be able to seek help either at this point!!
                         event.accepted = true
                         //% Just Go to help if any
                         mVScreen.source ="qrc:/qml//Help.qml"

                    }
                    break;
            }
        }

     } // endof keys.onPressed





} // eof mVScreen

