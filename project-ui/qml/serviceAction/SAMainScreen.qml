/***********************************************************************
**
** SAMainScreen.qml  
**
************************************************************************/
import Qt 4.7
import QtQuick 1.0
import com.ecolab.components 1.0
//import GarfunkelResourceStrings 0.1
import "../views"

ServiceActionMainView
{
    id: mSAScreen
    breadcrumb:  "Service Actions" 

    //softKeyIconList: ["qrc:/images/home.png", "qrc:/images/back-icon.png", "qrc:/images/status.png", "qrc:/images/help-icon.png"]
    //NGC Softkey Images
    softKeyIconList: ["qrc:/images/ngc/HomeOut.png", "qrc:/images/ngc/BackOut.png", "qrc:/images/ngc/BlankButtonOut.png", "qrc:/images/ngc/HelpOut.png"]



   menuModel: ListModel
        {
            ListElement { name: "Diagnostics";       qmlFile: "DMainScreen.qml" }
            ListElement { name: "S Block ";       qmlFile: "qml/Help.qml" }
            ListElement { name: "P Block";       qmlFile: "qml/Help.qml" }
            ListElement { name: "H2 Block";       qmlFile: "qml/Help.qml" }
            ListElement { name: "O Products";     qmlFile: "qml/Help.qml" }
            ListElement { name: "Actions";        qmlFile: "qml/PushDataToEnvision.qml" }
        }

    property variant qmlList: [
            "qrc:/qml/diagnostics/DMainScreen.qml",
            "qrc:/qml//Help.qml",
            "qrc:/qml//Help.qml",
            "qrc:/qml//Help.qml",
            "qrc:/qml//Help.qml",
            "qrc:/qml/serviceAction/InforScreen.qml"
    ]


    onEnterPressed:
    {
      mSAScreen.source = qmlList[currentIndex]
      console.log("Wow CurrentIdex = " + currentIndex + " Entered")

      if ( currentIndex == 0)
      {
        //Enable Diagnostics Mode
        console.log("Enabling Diagnostic Mode");
        diagcontext.diagnosticsTestRequest = true;
       }
    }


     Component.onCompleted: {
 
        // call function here once instance is created!!
    }


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
                        // HOME!
                        event.accepted = true;
                        console.log("F1: Welcome Home!!");
                        mSAScreen.source ="qrc:/qml//MainScreen.qml";
                    }
                    break;
                case Qt.Key_F2:
                    {
                        //Back to Home!!
                        event.accepted = true;
                        console.log("F2: Back to Home!!");
                        mSAScreen.visible = false;
                        mSAScreen.focus   = false;
                        mSAScreen.goBack();
                    }
                    break;
                case Qt.Key_F3:
                    {
                        //event.accepted = true
                        //main.goBack() // Status but just go back for now!!
                   }
                    break;
                case Qt.Key_F4:
                    {

                        event.accepted = true;
                        console.log("F4: Help!");
                        main.source ="qrc:/qml//Help.qml";
                    }
                    break;
            }
        }

    } // endof keys.onPressed


    
} // eof mSAScreen

