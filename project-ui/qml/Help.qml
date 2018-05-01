import Qt 4.7

import "views"

GView {
    id: generalHelp
    
    breadcrumb: ""
    numberedbreadcrumb: ""

    //softKeyIconList: ["qrc:/images/back-icon.png", "", "", ""]
    softKeyIconList: ["qrc:/images/ngc/BlankButtonOut.png", "qrc:/images/ngc/BackOut.png", "qrc:/images/ngc/BlankButtonOut.png", "qrc:/images/ngc/BlankButtonOut.png"]
    //property string videoDir: "file:///external_flash_a/multimedia/opl/"
    
    Item 
	{
		 //anchors.centerIn: parent.left

		Row 
		{
            id: dialogBox
            //anchors.fill: parent
			spacing: 50
			Image
			{
			  	id: infoimage
				source: "qrc:/images/Alarm_Telephone.png"
				height : 100
				width : 100
			}

            Text 
			{
                //text: (systemcontext.locale==0) ? "1-800-352-5326" : customerInfoData.phoneNumber
                text: "1-800-352-5326" 
                font.pixelSize: 20
                font.bold: true
                color: "black"
                
            }
        }
	}

/*
    Item {
                id : item1
                anchors.fill : parent
         Connections
                {
                target: systemcontext
                onLocaleChanged:
                {

                                
                }
        }

    }
*/
    Keys.onPressed: 
	{
        if (!event.isAutoRepeat) 
		{
            switch(event.key) 
			{
                case Qt.Key_Up:
                break;
                case Qt.Key_Right:
                break;
                case Qt.Key_Down:
                break;
                case Qt.Key_Left:
                break;
                case Qt.Key_F1:
                {
					event.accepted = true
                }
                break;
                case Qt.Key_F2:
                {
					generalHelp.goBack()
					event.accepted = true
                }
                break;
                case Qt.Key_F3:
                {
					event.accepted = true
                }
                break;
                case Qt.Key_F4:
                {
					event.accepted = true
                }
                break;
            }
        }

   event.accepted = true
 }
}
