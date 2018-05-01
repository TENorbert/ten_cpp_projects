/* Use For  Right Arrow Image Button */
import Qt 4.7

Item {
        id: imagebutton
        width: bImage.width; height: bImage.height
        
        property string buttonImage: ""
	
        Rectangle{
        	 id: bImage
       	 	 width: 30; height: 30
                 x: 448; y: 136
                 
                 color: "lightsteelblue"
                 radius: 8
        	
                  Image {
           	  	id: image
           	  	anchors{
                	  	fill: parent
                                margins: 0
                	  }
                 	rotation: +90
			fillMode: Image.PreserveAspectFit
           		source: buttonImage
                  }

        }

}






