/***********************************************************************
**
** NextPageScreen.qml  
**
************************************************************************/
import Qt 4.7
import QtQuick 1.0
import com.ecolab.components 1.0
//import GarfunkelResourceStrings 0.1
import "../views"

NextPageView
{
    id: dNextPageScreen
    breadcrumb:  "Page 2" 

    //softKeyIconList: ["qrc:/images/home.png", "qrc:/images/back-icon.png", "qrc:/images/on.png", "qrc:/images/help-icon.png"]
    arrowImage: "qrc:/images/condor/leftBlueArrow.png"


    menuModel: ListModel
        {
            ListElement { name: "Item 1";       qmlFile: "qml//Help.qml" }
            ListElement { name: "Item 2";       qmlFile: "qml//Help.qml" }
            ListElement { name: "Item 3";       qmlFile: "qml/Help.qml" }
            ListElement { name: "Item 4";       qmlFile: "qml/Help.qml" }
            ListElement { name: "Item 5";       qmlFile: "qml/Help.qml" }
            ListElement { name: "Item 6";       qmlFile: "qml/Help.qml" }
        }

    property variant qmlList: [
            "qrc:/qml//Help.qml",
            "qrc:/qml//Help.qml",
            "qrc:/qml//Help.qml",
            "qrc:/qml//Help.qml",
            "qrc:/qml//Help.qml",
            "qrc:/qml//Help.qml"
    ]


    onEnterPressed:
    {
      dNextPageScreen.source = qmlList[currentIndex]
      console.log("Wow CurrentIdex = " + currentIndex + " Entered")
    }



    /*
    function updateModel()
    {

            var noOfWashers = 6
            var i = 0;
            //menuModel.clear();
            for (i=1;i<noOfWashers;i++)
            {
                console.log("washerno="+i);
            //	menuModel.append({"symbol":"qrc:/images/wash"+(1)+".png", "name":"Test" })
            }
            //console.log("menu.count="+count);

    }
    */

     Component.onCompleted: {
 
 	//updateModel();
    }


    
} // eof dNextPageScreen

