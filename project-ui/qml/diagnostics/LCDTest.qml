import Qt 4.7

import com.ecolab.components 1.0
//import GarfunkelResourceStrings 0.1
import "../views"


Rectangle {
    id: screen 

    signal goBack()

    Rectangle {
        id: view
        anchors.fill: parent
        color: "lightsteelblue" //"#0082c8"

        /*
            Timer used to show the specified color for two second and then make it disappear.
        */
        Timer {
            id: displayTimer
            interval: 2000; running: false; repeat: false
            onTriggered: colorTest.visible = false
        }

        /*
            A full screen overlay to display the specified color.
        */
        Rectangle {
            id: colorTest
            anchors.fill: parent
            visible: false
            z: 2
            //font.family : screenfont
            //font.bold : fontBold 
        }

        Item {
            id: main 
            anchors { fill: parent; margins: 10; }

            GBreadcrumb {
                id: breadcrumb
                anchors { top: parent.top; margins: 5 }
                width: (numberedbreadcrumb.text == "" ? parent.width: (parent.width - numberedbreadcrumb.width))
                text: "LCD Test"
                 
                
               // text: GarfunkelLM.GetTMLanguageStringByID(ResourceString.DiagnosticsMenu)+">"+GarfunkelLM.GetTMLanguageStringByID(ResourceString.CondorController)+">"+GarfunkelLM.GetTMLanguageStringByID(ResourceString.LCDTest)    // "Diagnostics >Condor >LCD Test"
            }
           
            
            Text {
                id: numberedbreadcrumb
                anchors.top: parent.top
				anchors.right: parent.right; 
				anchors.rightMargin: 10;
				anchors.topMargin: 40;
                width: text.width
				color: "darkblue" //"white"
				font { pixelSize: 20; }
				elide: Text.ElideLeft
				text : Date()
                font.family: "helvitica" //numberedbreadcrumbfont
                font.bold: fontBold
            }
            
           
            

            Item {
                id: container
                anchors { top: breadcrumb.bottom; left: parent.left; bottom: softkeys.top; right: parent.right; topMargin: 5; bottomMargin: 10 }

                Text {
                    id: instructionText
                    anchors { top: parent.top; topMargin: 65 }
                    width: parent.width
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 20
                    wrapMode: Text.WordWrap
                    color: "darkblue" //"white"
                    text: "PRESS KEY"
                    font.bold: true
                    //text: GarfunkelLM.GetTMLanguageStringByID(ResourceString.LCDTestInstruction)  //"Press a key below to change the screen to the specified color."
                    font.family : screenfont
                    //font.bold : fontBold 
                }
            }

            GSoftkeys {
                id: softkeys
                anchors.bottom: parent.bottom
                softkeyTextList:["RED","BACK","GREEN","BLUE" ]
               // softkeyTextList: [ GarfunkelLM.GetTMLanguageStringByID(ResourceString.Back), GarfunkelLM.GetTMLanguageStringByID(ResourceString.Red) ,GarfunkelLM.GetTMLanguageStringByID(ResourceString.Green),  GarfunkelLM.GetTMLanguageStringByID(ResourceString.Blue)]
            }


/*
        Item {
	
		id : itemcondorComponents
		anchors.fill : parent    
    	 	
		Connections 
		{
        	target: GarfunkelLM
        	onLocalizedStringsChanged: 
			{
				breadcrumb.text= GarfunkelLM.GetTMLanguageStringByID(ResourceString.DiagnosticsMenu)+">"+GarfunkelLM.GetTMLanguageStringByID(ResourceString.CondorController)+">"+GarfunkelLM.GetTMLanguageStringByID(ResourceString.LCDTest)    // "Diagnostics >Condor >LCD Test"
        	}
    	}
    
    }
*/

            Keys.onPressed: {
                if (!event.isAutoRepeat)
                {
                    if (displayTimer.running)
                    {
                        /*
                            Any key hides the view if it's up.
                        */
                        colorTest.visible = false
                        displayTimer.stop()
                    }
                    else
                    {
                        switch (event.key) {
                            case Qt.Key_Up:
                                break;
                            case Qt.Key_Right:
                                break;
                            case Qt.Key_Down:
                                break;
                            case Qt.Key_Left:
                                break;
                            case Qt.Key_Return:
                                break;
                            case Qt.Key_F1:
                                colorTest.color = "red"
                                break;
                            case Qt.Key_F2:
                                screen.goBack()
                                break;
                            case Qt.Key_F3:
                                colorTest.color = "green"
                                break;
                            case Qt.Key_F4:
                                colorTest.color = "blue"
                                break;
                        }

                        /*
                            Start the timer.
                        */
                        if (event.key == Qt.Key_F1 || event.key == Qt.Key_F3 || event.key == Qt.Key_F4)
                        {
                            colorTest.visible = true
                            displayTimer.restart()
                        }
                    }
                }

                event.accepted = true
            }
        }
    }

    focus: true
    Keys.forwardTo: main
}
