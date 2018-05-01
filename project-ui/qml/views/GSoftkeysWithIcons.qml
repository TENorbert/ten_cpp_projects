import QtQuick 1.0

Item {
    id: softkeyswithicons
    width: parent.width; 
    //height: btn1.height + hr.height + 5
    height: img1.height + hr.height + 5

    property variant softkeyIconList: ["", "", "", ""]

    property alias btnIcon1: img1.source
    property alias btnIcon2: img2.source
    property alias btnIcon3: img3.source
    property alias btnIcon4: img4.source
 
   //% No Need for this Line
   
    Rectangle {
        id: hr
        //width: parent.width; height: 2
        width: 0; height: 0
        anchors { bottom: buttons.top; bottomMargin: 5; }
        //color: "#0082c8" //"#616365"
    }
  
    Item {
	id: buttons
        //width: parent.width; height: btn1.height
        width: parent.width; height: img1.height
        anchors.bottom: parent.bottom

       
	Rectangle {
        id: btn1
        width: img1.width; height: img1.height;
        x: 7
        radius: 10
        
        color: "lightsteelblue" //"#0082c8" //"#616365"
        
       //gradient: Gradient {
       //    GradientStop {color: "#CFF7FF"; position: 0.0}
       //    GradientStop {color: "#0082c8"; position: 0.57}
       //    GradientStop {color: "#719FCB"; position: 0.9}
       //}
       


       Image {
			id: img1
                        width: 100; height: 60
                        source: softkeyIconList[0]
                        anchors.fill: parent
                        anchors.margins: 0
                        fillMode: Image.PreserveAspectFit

                }
        }


      
	Rectangle {
        	id: btn2
        	width: img2.width; height: img2.height;
        	x:122  //125 //122
        	radius: 10
        	color: "lightsteelblue" //"#0082c8" //"#616365"
        
		//color: "#0082c8"//"#616365"
        	//gradient: Gradient {
           	//GradientStop {color: "#CFF7FF"; position: 0.0}
           	//GradientStop {color: "#0082c8"; position: 0.57}
           	//GradientStop {color: "#719FCB"; position: 0.9}
      		// }	
       


                Image {
			id: img2
                        width: 100; height: 60
                        source: softkeyIconList[1]
                        anchors.fill: parent
                        anchors.margins: 0
                        fillMode: Image.PreserveAspectFit

                }
        }





        
	 Rectangle {
        	id: btn3
        	width: img3.width; height: img3.height;
        	x: 238 //241 //238
        	radius: 10
        	//width: 75; height: 50;
        	color: "lightsteelblue" //"#0082c8" //"#616365"
        //color: "#0082c8" //"#616365"
        //gradient: Gradient {
        //   GradientStop {color: "#CFF7FF"; position: 0.0}
        //   GradientStop {color: "#0082c8"; position: 0.57}
        //   GradientStop {color: "#719FCB"; position: 0.9}
        //     }
       


            Image {
			id: img3
  
			width: 100; height: 60
                        source: softkeyIconList[2]
                        anchors.fill: parent
                        anchors.margins: 0
                        fillMode: Image.PreserveAspectFit

                }
        }


       
	Rectangle {
       		 id: btn4
        	 width: img4.width; height: img4.height;
        	 x: 354 //354
        	 radius: 10
                 color: "lightsteelblue" //"#0082c8" //"#616365"
       
	//color: "#0082c8" //"#616365"
        //gradient: Gradient {
        //   GradientStop {color: "#CFF7FF"; position: 0.0}
        //   GradientStop {color: "#0082c8"; position: 0.57}
        //   GradientStop {color: "#719FCB"; position: 0.9}
        //     }
        
      

                Image {
			id: img4
			width: 100; height: 60
                        source: softkeyIconList[3]
			anchors.fill: parent
			anchors.margins: 0
			fillMode: Image.PreserveAspectFit
                }

	}

        
   }

}
