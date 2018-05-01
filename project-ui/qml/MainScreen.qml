import Qt 4.7
import QtQuick 1.0
import com.ecolab.components 1.0
//import GarfunkelResourceStrings 0.1

import "views"


GarfunkelMainView
{
    id: mScreen

    breadcrumb:  "Main Menu"
    //pagetitlebreadcrumbText: "Main Menu" 

    //softKeyIconList: ["qrc:/images/home.png", "qrc:/images/select-formula.png", "qrc:/images/laundry-load-counts-1.png", "qrc:/images/status.png"]
	
    menuModel: ListModel 
    {
		//ListElement { symbol: "qrc:/images/wash1.png";   name:"Test" }
		ListElement {  symbol: "qrc:/images/R5images/CustomerDetails.png";  name:"Data Entry" }
		ListElement {  symbol: "qrc:/images/R5images/Status.png";  name:"System Status" }
		ListElement {  symbol: "qrc:/images/R5images/DownloadDataSmall.png";  name:"Download Data" }
		ListElement {  symbol: "qrc:/images/R5images/Configure.png";  name:"Configure" }
		ListElement {  symbol: "qrc:/images/R5images/ServiceActions.png";  name:"Service Actions" }
		ListElement {  symbol: "qrc:/images/R5images/UserOptions.png";  name:"User Options" }
		
    }

    //% Put screens as qml files
    property variant qmlList: [
    "qrc:/qml//Help.qml",
    "qrc:/qml//systemStatus/SSMainScreen.qml",
    "qrc:/qml//Help.qml",
    "qrc:/qml//Help.qml",
    "qrc:/qml//serviceAction/SAMainScreen.qml",
    "qrc:/qml//Help.qml"
            ]


    onEnterPressed: {
          console.log("Wow CurrentIdex = " + currentIndex + " Found!!!")
          mScreen.source = qmlList[currentIndex]
        }



    Component.onCompleted: {

               // Call a fxn
                }

}

