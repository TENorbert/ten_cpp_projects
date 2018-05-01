import Qt 4.7

import com.ecolab.components 1.0
import "views"

GView 
{
    id: passwordMenu

	//btnText1: "Back"
	//btnText2: ""
	//btnText3: ""
	//btnText4: "Help"
    	softKeyIconList: ["qrc:/images/back-icon.png", "", "", "qrc:/images/help-icon.png"]
	property int  password: 0
    property bool loggedin: false
 
 
 
 
    Item 
	{
        anchors.fill: parent

        Rectangle 
		{
            id: dialogBox
            anchors.fill: parent
            color: "#0082c8"
			Column
			{
				spacing:30
				Text 
				{
					text: "Program Menu"
					font.pixelSize: 30
					color: "white"
				}	
			
				Row 
				{
					spacing:10
					Text 
					{
						text: "Password Page : Please Enter Password:"
						font.pixelSize: 30
						color: "white"
					}
					Image
					{
						//height:56
						//width:105
						source: "qrc:/images/password.png"
					} 
				}
			}
        }
        Connections 
        {
            target: passwdcontext
            onLoginChanged: {
            	                screenTimeout.stop()
            					passwordMenu.source = "MainMenu.qml"
            					aquanomics.registerUserLogin()
				                aquanomics.loggedIn = true
			                
            				}
        }
        /* Screen timeout timer. */
        Timer {
            id: screenTimeout
            interval: 20000; running: false; repeat: false  //timeout of 20 seconds 
            onTriggered: {
                console.log("Screen timeout")
                passwordMenu.goBack()
            }
        }
	}
	
	Component.onCompleted: {
 
 					screenTimeout.restart()
 				}
	
	Keys.onPressed: 
    {
        if (!event.isAutoRepeat)
        {
            passwdcontext.loginStatus = event.key;
            if(aquanomics.loggedIn !=true)
            screenTimeout.restart()
            switch (event.key) 
            {
                case Qt.Key_F1:
                	{
                	aquanomics.loggedIn = false
                    passwordMenu.goBack()
                    }
                    break;
                case Qt.Key_F4:
                    passwordMenu.source = "Help.qml"
                    break;
                case Qt.Key_Up:
                case Qt.Key_Right:
                case Qt.Key_Down:
                case Qt.Key_Left:
                    break;
            }
        }
		event.accepted = true
    }
}
