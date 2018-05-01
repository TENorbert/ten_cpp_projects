/***********************************************************************
**
** CondorScreen.qml  
**
************************************************************************/
import Qt 4.7
import QtQuick 1.0
import com.ecolab.components 1.0
//import GarfunkelResourceStrings 0.1
import "../views"

InnerGridView
{
    id: dCScreen
    breadcrumb:  "Condor" 

    softKeyIconList: ["qrc:/images/ngc/BlankButtonOut.png" , "qrc:/images/ngc/BackOut.png", "qrc:/images/ngc/BlankButtonOut.png", "qrc:/images/ngc/BlankButtonOut.png"]


   menuModel: ListModel
            {
                ListElement { name: "Front Key Test";       qmlFile: "FrontKeysTest.qml" }
                ListElement { name: "LCD Test";       qmlFile: "LCDTest.qml" }
                ListElement { name: "Condor Version.";      qmlFile: "CondorVersionScreen.qml" }
            }


        property variant qmlList: [
                "qrc:/qml//diagnostics/FrontKeysTest.qml",
                "qrc:/qml//diagnostics/LCDTest.qml",
                "qrc:/qml//Help.qml",
        ]



        onEnterPressed:
        {
          dCScreen.source = qmlList[currentIndex]
          console.log("Wow CurrentIdex = " + currentIndex + " Entered")
        }



         Component.onCompleted: {

         //Call a function here Once Instance is created!!
        }

} // eof dCScreen

