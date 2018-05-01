/* Use For  Right Arrow Image Button */
import Qt 4.7
import "../views"

Item {
        id: imagebutton
        width: rImage.width; height: rImage.height
        
        property string rbuttonImage: ""
	
        Rectangle{
        	 id: rImage
       	 	 width: 30; height: 30
                 x: 448; y: parent.height/2 // 136
                 
                 color: "lightsteelblue"
                 radius: 8
        	
                  Image {
           	  	id: image
           	  	anchors{
                	  	fill: parent
                                margins: 0
                	  }
                 	rotation: +180
                        clip: true
			fillMode: Image.PreserveAspectFit
           		source: rbuttonImage
                  }

        }

}






