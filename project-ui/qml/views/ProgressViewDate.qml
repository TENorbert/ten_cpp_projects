import Qt 4.7

import com.ecolab.components 1.0

Rectangle {
    id: screen
    anchors.fill: parent

    default property alias content: main.children

    property bool enableAdjustBar: true
	
    property variant minValue : new Date(2012,1,1,0,0,0,0) // fromDate
    property variant maxValue : new Date(2012,3,20,0,0,0,0) //toDate
    property variant step: 1
    property variant currentFromValue: minValue
    property variant currentToValue: maxValue
    property string unitLabel1: "From " + (systemcontext.unitOfMeasure == 0? "(MM.DD.YYYY)" : "(DD.MM.YYYY)")
    property string unitLabel2: "To " + (systemcontext.unitOfMeasure == 0? "(MM.DD.YYYY)" : "(DD.MM.YYYY)")
    property int totalLCount: 0    
    property alias customerName: custname.text
    property alias loadIcon: loadImage.source
		
    property alias softKeyIconList: softkeys.softkeyIconList
    property alias btnIcon1: softkeys.btnIcon1
    property alias btnIcon2: softkeys.btnIcon2
    property alias btnIcon3: softkeys.btnIcon3
    property alias btnIcon4: softkeys.btnIcon4

    property alias source: progressLoader.source
    property alias footer: totalLoad.text 
	
    signal valueSaved(double value)
    signal valueUpdated(double value)
    signal goBack()
	property variant screenfont :  AquanomicsLM.GetPrimaryLangaugeFontName()
    property bool fontBold :  AquanomicsLM.GetPrimaryLangaugeFontBoldStatus()

    property bool progressBarFrom : true

            function reloadFontProperties()
    {
        screenfont =  AquanomicsLM.GetPrimaryLangaugeFontName()
        fontBold =  AquanomicsLM.GetPrimaryLangaugeFontBoldStatus() 
    }

    Loader {
        id: progressLoader
        anchors.fill: parent
        source: ""

        onSourceChanged: progressLoader.focus = true
        onLoaded: progressView.visible = false;
    }
    Connections {
        target: progressLoader.item
        onGoBack: {
            progressLoader.source = "";
            reloadFontProperties();
            progressView.visible = true
            progressView.focus = true
        }
    }

    function checkCurrentValueRange(min, max, value) {
        var returnValue = value;
        if (value > max) {
            returnValue = max;
        } else if (value < min) {
            returnValue = min;
        } else {
            /* Nothing. */
        }

        return returnValue;
    }

    function addDay(datevalue) {
        var returnValue = datevalue;
        returnValue.setDate(datevalue.getDate()+ 1);
		return returnValue;
    }
    function substractDay(datevalue) {
        var returnValue = datevalue;
        returnValue.setDate(datevalue.getDate()- 1);
		return returnValue;
    }
   function setStartOfDay(datevalue) {
        var returnValue = datevalue;
        returnValue.setHours(0,0,0,0);
		return returnValue;
    }
    function dayDifference(from, to) {
		var days = 0;
		var millisecondsPerDay = 1000 * 60 * 60 * 24;
		if(from>to)
		days = (from-to)/millisecondsPerDay;
		else
		days = (to-from)/millisecondsPerDay;
		return Math.round(days);
	}
	
	

    Rectangle {
        id: progressView
        anchors.fill: parent
        color: "#0082c8"

        /*
            This value is what is actually used to draw the progress bar. If we
            modify screen.currentValue directly from this Component, we break
            the connections between the context value that is aliased to it, so
            when the db updates, the value isn't reflected on the screen.
        */
        property variant fromValue: screen.currentFromValue
		property variant toValue: screen.currentToValue

        Connections {
            target: screen

            /*
                Ensure that we never attempt to draw a progress bar that is above 100% or below 0%.
            */
            onCurrentFromValueChanged: progressView.fromValue = screen.checkCurrentValueRange(screen.minValue, screen.maxValue, screen.currentFromValue)
			onCurrentToValueChanged: progressView.toValue = screen.checkCurrentValueRange(screen.minValue, screen.maxValue, screen.currentToValue)
            onMaxValueChanged: {
			                   progressView.fromValue = screen.checkCurrentValueRange(screen.minValue, screen.maxValue, progressView.fromValue)
							   progressView.toValue = screen.checkCurrentValueRange(screen.minValue, screen.maxValue, progressView.toValue)
							   }
            onMinValueChanged: {
			                   progressView.fromValue = screen.checkCurrentValueRange(screen.minValue, screen.maxValue, progressView.fromValue)
							   progressView.toValue = screen.checkCurrentValueRange(screen.minValue, screen.maxValue, progressView.toValue)
							   }
        }

        Component.onCompleted: {
		                         progressView.fromValue = screen.checkCurrentValueRange(screen.minValue, screen.maxValue, progressView.fromValue);
								 progressView.toValue = screen.checkCurrentValueRange(screen.minValue, screen.maxValue, progressView.toValue);
							    } 

        onFromValueChanged: screen.valueUpdated(progressView.fromValue)
		onToValueChanged: screen.valueUpdated(progressView.toValue)

        Item {
            id: container
            anchors { fill: parent; margins: 5; }
            Text {
                id: custname
                anchors.top: parent.top
                width: parent.width
				font.pixelSize: 20
				color: "white"
                font.family : screenfont
                font.bold : fontBold
            }
			Image {
                id: loadImage
                anchors.right:parent.right 	
                anchors.rightMargin: 5				
            }			

            Item {
                id: main
                anchors { top: custname.bottom; left: parent.left; bottom: softkeys.top; right: parent.right; }
				anchors.topMargin: 15
                width: parent.width
                
				Column {
                    spacing: 20
					anchors.horizontalCenter: parent.horizontalCenter
					    Text {
                            id: progressText1
                            text: unitLabel1+" :  "+Qt.formatDate(progressView.fromValue, (systemcontext.unitOfMeasure == 0? "MM.dd.yyyy" : "dd.MM.yyyy")) 
                            color: font_color()
                            font { pixelSize: 20; weight: Font.Bold}
							function font_color()
							{
							  if(progressBarFrom) {
							  return "white"
							  }
							  else {
							  return "black"
							  }
							}
                        }
						
						Text {
                            id: progressText2
                            text:  unitLabel2+"      :  " +Qt.formatDate(progressView.toValue, (systemcontext.unitOfMeasure == 0? "MM.dd.yyyy" : "dd.MM.yyyy")) 
                            color: font_color()   
                            font { pixelSize: 20; weight: Font.Bold}
							function font_color()
							{
							  if(progressBarFrom) {
							  return "black"
							  }
							  else {
							  return "white"
							  }
							}
                            font.family : screenfont
                        }
                    }

			}

            Rectangle {
                width: 304; height: 30
                color: "white"
                id: progressBar
                // we have 300px to use from 0% to 100%
                // a step in px is 300/(max-min)
                    Rectangle {
                        property variant pxStep: 300/(screen.maxValue - screen.minValue)
				     	x : (2 + (progressView.fromValue * pxStep) - (screen.minValue * pxStep))
                        width:(progressView.toValue-progressView.fromValue) * pxStep
                        height: 26
                        y: 2
                        color: "#616365"
                    }
							
			    anchors.horizontalCenter: parent.horizontalCenter
				anchors.bottom: totalLoad.top
				anchors.bottomMargin: 10
            }

			Text 
			{
				id : totalLoad 
				anchors.bottom : softkeys.top 
				anchors.bottomMargin: 10
				anchors.horizontalCenter: parent.horizontalCenter
				text : "Total : " + totalLCount + "  Cycles,  " + totalLCount + " KG"
				color : "white"
				font.pixelSize: 20
                font.family : screenfont
                font.bold : true
			}

            SoftkeysWithIcons {
                id: softkeys
                anchors.bottom: parent.bottom

                softkeyIconList: ["", "", "", "qrc:/images/help-icon.png"]
            }
        }

        focus: true
        Keys.forwardTo: parent
        Keys.onPressed: {
            switch (event.key) {
                case Qt.Key_Up:
				    {
                       progressBarFrom = ! progressBarFrom
                    }
					break;
                case Qt.Key_Right:
                    /* Increase progress bar */
					totalLCount = 0;
					if(progressBarFrom)
					{
					  if ((progressView.fromValue < screen.maxValue)&&(progressView.fromValue < progressView.toValue)) {
                      progressView.fromValue = addDay(progressView.fromValue)   // += screen.step;
						}
					}
                    else {					
					  if ((progressView.toValue < screen.maxValue)) {
                      progressView.toValue = addDay(progressView.toValue)   // += screen.step;
						}
                    }
                    currentFromValue = progressView.fromValue
		    currentToValue = progressView.toValue
                    break;
                case Qt.Key_Down:
				    { 
				    progressBarFrom = ! progressBarFrom
					}
					break;
                case Qt.Key_Left:
                    /* Decrease progress bar */
					totalLCount = 0;
					if(progressBarFrom)
					{
						if (progressView.fromValue > screen.minValue) {
                        progressView.fromValue = substractDay( progressView.fromValue)
						}
					}
					else
					{
						if ((progressView.toValue > screen.minValue)&&(progressView.toValue > progressView.fromValue)) {
                        progressView.toValue =  substractDay(progressView.toValue)
						}
					}
                    currentFromValue = progressView.fromValue
		    currentToValue = progressView.toValue
                    break;
                case Qt.Key_F1:
					screen.goBack();
				    console.log("Emitting goback signal");
                    break;
                case Qt.Key_F4:
                    {
                        screen.source ="../Help.qml"
                        event.accepted = true
                    }break;
                case Qt.Key_F3:
                    if (!event.isAutoRepeat) {
//                        screen.valueSaved(progressView.fromValue)
//						screen.valueSaved(progressView.toValue)
                      totalLCount = dayDifference(progressView.fromValue,progressView.toValue)
                        //screen.goBack();
                    }

                    break;
                case Qt.Key_F2:
                    break;
            }

            event.accepted = true
        }
    }
}
