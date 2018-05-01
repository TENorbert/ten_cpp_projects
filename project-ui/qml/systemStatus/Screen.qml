/***********************************************************************
**
** Screen.qml  
**
************************************************************************/
import Qt 4.7
import QtQuick 1.0
import com.ecolab.components 1.0
//import GarfunkelResourceStrings 0.1
import "../views"

ViewGrid
{
        id: dScreen
        breadcrumb:  "Page 2"

        //softKeyIconList: ["qrc:/images/home.png", "qrc:/images/back-icon.png", "qrc:/images/on.png", "qrc:/images/help-icon.png"]


        Item {
            id: connections
            anchors.fill: parent

            Connections {
                  target: item
                  onGoBack: {
                     source = "qrc:/qml//SSMainScreen.qml"
                     reloadFontProperties()
                     menuView.visible = true
                     menuView.focus = true
                     mainView.visible = true
                     mainView.focus = true
                }
            }
        }


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
          dScreen.source = qmlList[currentIndex]
          console.log("Wow CurrentIdex = " + currentIndex + " Entered")
        }




        Component.onCompleted: {
          //Define a funxtion
        }

        Component.onDestruction:  {
           mainView.activeFocus ? console.log("I Have Active Focus") : console.log("I don't have Active Focus")
            // mainView.state = ""

        }


        Keys.onPressed: {
            // disable auto repeat //
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
                            console.log("F1: Welcome Home!!")
                            dScreen.source ="qrc:/qml//MainScreen.qml"                           
                        }
                        break;
                    case Qt.Key_F2:
                        {
                            //Back to Home!!
                            event.accepted = true;
                            console.log("F2: Back to Home!!");
                            dScreen.visible = false;
                            dScreen.focus   = false;
                            dScreen.goBack();
                        }
                        break;
                    case Qt.Key_F3:
                        {
                            //main.goBack(); // Status but just go back for now!!
                            //event.accepted = true
                       }
                        break;
                    case Qt.Key_F4:
                        {
                            event.accepted = true
                            console.log("F4: HELP!!")
                            dScreen.source ="qrc:/qml//Help.qml"

                        }
                        break;
                }
            }

        }



} // eof dScreen

