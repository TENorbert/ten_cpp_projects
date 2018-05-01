import Qt 4.7
import AquanomicsResourceStrings 0.1
import com.ecolab.components 1.0

Rectangle {
    id: screen
    anchors.fill: parent

    default property alias content: main.children

    property bool enableAdjustBar: true
    property double minValue: 0
    property double maxValue: 100
    property double step: 1
    property double currentValue: 50

    property string unitLabel: ""

    property alias breadcrumb: breadcrumb.text
	property alias washerNo: washerImage.source
	property alias formulaText:formulatext.text
	
    property alias softKeyIconList: softkeys.softkeyIconList
    property alias btnIcon1: softkeys.btnIcon1
    property alias btnIcon2: softkeys.btnIcon2
    property alias btnIcon3: softkeys.btnIcon3
    property alias btnIcon4: softkeys.btnIcon4

	property alias source: progressLoader.source
	
    signal valueSaved(double value)
    signal valueUpdated(double value)

    property variant screenfont :  AquanomicsLM.GetPrimaryLangaugeFontName()
    property bool fontBold :  AquanomicsLM.GetPrimaryLangaugeFontBoldStatus() 
    
    
        function reloadFontProperties()
    {
       //   console.log("************Inside reloadFontProperties*******");
        screenfont =  AquanomicsLM.GetPrimaryLangaugeFontName()
        fontBold =  AquanomicsLM.GetPrimaryLangaugeFontBoldStatus() 
       //   console.log("************DONE*******");
        
    }

    signal goBack()

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

    /*
        Function to check that value is in the range min to max. If it's
        greater than the max it returns the max, if it's less than the
        min it returns the min.
    */
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
        property double value: screen.currentValue

        Connections {
            target: screen

            /*
                Ensure that we never attempt to draw a progress bar that is above 100% or below 0%.
            */
            onCurrentValueChanged: progressView.value = screen.checkCurrentValueRange(screen.minValue, screen.maxValue, screen.currentValue)
            onMaxValueChanged: progressView.value = screen.checkCurrentValueRange(screen.minValue, screen.maxValue, progressView.value)
            onMinValueChanged: progressView.value = screen.checkCurrentValueRange(screen.minValue, screen.maxValue, progressView.value)
        }

        Component.onCompleted: progressView.value = screen.checkCurrentValueRange(screen.minValue, screen.maxValue, progressView.value)

        onValueChanged: screen.valueUpdated(progressView.value)

        Item {
            id: container
            anchors { fill: parent; margins: 10; }
            OPLBreadcrumb {
                id: breadcrumb
                anchors.top: parent.top
                width: parent.width
                breadcrumbfont :  brdcrumbfont
                breadcrumbfontbold : fontBold  

            }
			Image {
                id: washerImage
                anchors.top:breadcrumb.bottom 	
                anchors.topMargin: 5				
                width:60
				height:60
            }			
            OPLBreadcrumb {
                id: formulatext
                anchors.top: washerImage.bottom
				anchors.topMargin: 5
				width: parent.width
                breadcrumbfont :  screenfont
                breadcrumbfontbold : fontBold  
            }

            Item {
                id: main
                anchors { top: formulatext.bottom; left: parent.left; bottom: softkeys.top; right: parent.right; margins: 10; }
                width: parent.width

                Column {
						anchors.centerIn: parent
						spacing: 10
						visible: enableAdjustBar
                        Text {
                            id: progressText
                            text: AquanomicsLM.GetTMLanguageStringByID(ResourceString.Completed)+" : "+formatNumber(progressView.value) + unitLabel
                            font.family : screenfont
                            font.bold : fontBold
                            color: "white"    
                            height: 24  // needs to be same height as arrows so we can center vertically
                            font { pixelSize: 30; weight: Font.Bold}
                            anchors.horizontalCenter: parent.horizontalCenter
                            function formatNumber(number) {
                                if (screen.step < 1) {
                                    return number.toFixed(1)
                                } else {
                                    return number
                                }
                            }
                        }

                        Rectangle {
                            width: 304; height: 30
                            color: "white"

                            // we have 300px to use from 0% to 100%
                            // a step in px is 300/(max-min)
                            Rectangle {
                                id: progressBar

                                property double pxStep: 300/(screen.maxValue - screen.minValue)
                                width: ((progressView.value * pxStep) - (screen.minValue * pxStep))
                                height: 26
                                x: 2; y: 2
                                color: "#616365"
                        }
                    }
                }
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
                    /* fall-through */
                case Qt.Key_Right:
                    /* Increase progress bar */
                    break;
                case Qt.Key_Down:
                    /* fall-through */
                case Qt.Key_Left:
                    /* Decrease progress bar */
                    break;
                case Qt.Key_F1:
				    screen.goBack();
					console.log("Emitting goback signal");
                    break;
                case Qt.Key_F4:
                    // Help
                    //TODO: help not implemented
                    break;
                case Qt.Key_F3:
                    break;
                case Qt.Key_F2:
                    break;
                case Qt.Key_F4:
                {
                    screen.source ="../Help.qml"
                    event.accepted = true
                }break;
            }

            event.accepted = true
        }
    }
}
