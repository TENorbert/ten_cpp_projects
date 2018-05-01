/* Use For Bottom Tool Bar with 4 Button Images */
import Qt 4.7

Rectangle{
 
      id: bottomtoolbarbuttons 
      color: "#c0c0c0"
 
      property string bImage1: ""
      property string bImage2: ""
      property string bImage3: ""
      property string bImage4: ""
 
      anchors{
             fill: parent
             bottomMargin: 5
             leftMargin: 5
             rightMargin: 5
             }
      
     // Buttons in row    
     Row {
         spacing: 2
         ImageButton { id: ibutton1; color: "red"; width: 50; height: 40; bImage: bImage1; radius: 10 }
         ImageButton { id: ibutton2; color: "green"; width: 100; height: 50; bImage: bImage2; radius: 10 } 
         ImageButton { id: ibutton3; color: "blue"; width: ; height: 40; bImage: bImage3; radius: 10 }
         ImageButton { id: ibutton4; color: "yellow"; width: 50; height: 40; bImage:bImage4; radius: 10 }


}




}
