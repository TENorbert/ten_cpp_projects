/* Use For  Right Arrow Image Button */
import Qt 4.7

Item {
        id: imagebutton
        width: lImage.width; height: lImage.height
        
        property string lbuttonImage: ""
	
        Rectangle{
        	 id: lImage
       	 	 width: 30; height: 30
                 x: 5; y: parent.height/2 //138
                 
                 color: "lightsteelblue"
                 radius: 8
        	
                  Image {
           	  	id: image
           	  	anchors{
                	  	fill: parent
                                margins: 0
                	  }
                 	rotation: 0
                        clip: true
			fillMode: Image.PreserveAspectFit
           		source: lbuttonImage
                  }

        }

}






