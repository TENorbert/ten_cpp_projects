import Qt 4.7
import com.ecolab.components 1.0
//import GarfunkelResourceStrings 0.1
import "../views"

GView 
{
    id: condorKeys
    breadcrumb: "Front Keys Test"

  //  breadcrumb: GarfunkelLM.GetTMLanguageStringByID(ResourceString.DiagnosticsMenu)+">"+GarfunkelLM.GetTMLanguageStringByID(ResourceString.CondorController)+">"+GarfunkelLM.GetTMLanguageStringByID(ResourceString.FrontKeyTest)        // "Diagnostics > Condor > Front Keys"
    //numberedbreadcrumb: Date() //"#8.1.3"
	//softKeyTextList: ["",GarfunkelLM.GetTMLanguageStringByID(ResourceString.Back), "" ,""]
softKeyIconList: ["qrc:/images/ngc/BlankButtonOut.png", "qrc:/images/ngc/BackOut.png", "qrc:/images/ngc/BlankButtonOut.png", "qrc:/images/ngc/BlankButtonOut.png"]
    Item {
        id: main
        anchors.fill: parent

        Item {
            id: container
            anchors.fill: parent

            Text {
                id: instructionText
                anchors { top: parent.top; topMargin: 25 }
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 20
                font.bold: true
                wrapMode: Text.WordWrap
                color: "darkblue" //"white"
                text: "PRESS KEY"
              //  text: GarfunkelLM.GetTMLanguageStringByID(ResourceString.FrontKeyTestInstruction)              //"Press a softkey to test. The key name should appear below. Press back twice to return to the previous screen."
                font.family : screenfont
                //font.bold : fontBold 
            }

            /*
                Show the keycode of the pressed key.
            */
            Text {
                id: keypadTestResult
                anchors { top: instructionText.bottom; topMargin: 30 }
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 30
                font.bold: true
                color: "darkblue"//"white"
                font.family : screenfont
                //font.bold : fontBold 
            }

        }

        /*
            Timer used to show the keycode for one second and then make it disappear.
        */
        Timer {
            id: displayTimer
            interval: 1000; running: false; repeat: false
            onTriggered: keypadTestResult.text = ""
        }

        /*
            Flag indicating whether or not pressing F1 returns the controller to
            the previous screen. F1 must be press twice consecutively to go back.
        */
        property bool canGoBack: false
/*
                Item {
	
		id : itemcondorKeys
		anchors.fill : parent    
    	 Connections 
		{
        	target: GarfunkelLM
        	onLocalizedStringsChanged: 
			{
				condorKeys.breadcrumb= GarfunkelLM.GetTMLanguageStringByID(ResourceString.DiagnosticsMenu)+">"+GarfunkelLM.GetTMLanguageStringByID(ResourceString.CondorController)+">"+GarfunkelLM.GetTMLanguageStringByID(ResourceString.FrontKeyTest)
				instructionText.text = GarfunkelLM.GetTMLanguageStringByID(ResourceString.FrontKeyTestInstruction)
        	}
    	}
    
    }

*/
        Keys.onPressed: {
            if (!event.isAutoRepeat)
            {
                switch (event.key) {
                    case Qt.Key_Up:
                        keypadTestResult.text = "UP"
                        break;
                    case Qt.Key_Right:
                        keypadTestResult.text = "RIGHT"
                        break;
                    case Qt.Key_Down:
                        keypadTestResult.text = "DOWN"
                        break;
                    case Qt.Key_Left:
                        keypadTestResult.text = "LEFT"
                        break;
                    case Qt.Key_Return:
                        keypadTestResult.text = "ENTER"
                        break;
                    case Qt.Key_F1:
                        keypadTestResult.text = "F1"
                        break;
                    case Qt.Key_F2:
                        keypadTestResult.text = "F2"
                        /*
                            Only go back if F1 has been pressed twice in a row.
                        */
                        if (canGoBack)
                            condorKeys.goBack()

                        canGoBack = true
                        break;
                    case Qt.Key_F3:
                        keypadTestResult.text = "F3"
                        break;
                    case Qt.Key_F4:
                        keypadTestResult.text = "F4"
                        break;
                }

                /*
                    Reset the go back flag if F2 wasn't pressed.
                */
                if (event.key != Qt.Key_F2 && canGoBack == true)
                {
                    canGoBack = false
                }

                /*
                    Start the timer if it's not running, restart it if it is.
                */
                displayTimer.restart()
            }

            event.accepted = true
        }
    }

    Keys.forwardTo: main
}
