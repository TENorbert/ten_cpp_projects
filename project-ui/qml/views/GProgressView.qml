import QtQuick 1.0
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
    property bool displayDecimals: false
    property string unitLabel: ""

    property alias breadcrumb: breadcrumb.text
    property alias numberedbreadcrumb: numberedbreadcrumb.text
	property alias headertext: headerinfo.text
	property alias footertext: footerinfo.text
    
    property alias softKeyIconList: softkeys.softkeyIconList
    property alias btnIcon1: softkeys.btnIcon1
    property alias btnIcon2: softkeys.btnIcon2
    property alias btnIcon3: softkeys.btnIcon3
    property alias btnIcon4: softkeys.btnIcon4

    signal valueSaved(double value)
    signal valueUpdated(double value)

    signal goBack()
   	property variant screenfont :  AquanomicsLM.GetTMLangaugeFontName()
    property bool fontBold :  AquanomicsLM.GetTMLangaugeFontBoldStatus() 
    
    
        function reloadFontProperties()
    {
        screenfont =  AquanomicsLM.GetTMLangaugeFontName()
        fontBold =  AquanomicsLM.GetTMLangaugeFontBoldStatus() 
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

    /*
        Function to check that value is in the range min to max. If it's
        greater than the max it returns the max, if it's less than the
        min it returns the min.
    */
    function checkCurrentValueRange(min, max, value) {
	console.log("[checkCurrentValueRange] min : " + min + " ** max : " + max + " ** new value : " + value);
	console.log("Strp value : " + screen.step);
        var returnValue = value;
        if (value > max) {
            returnValue = max;
        } else if (value < min) {
            returnValue = min;
        } else {
            /* Nothing. */
        }

	if (screen.displayDecimals == true) { returnValue = returnValue.toFixed(5); }
	console.log("Return value : " + returnValue);
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

            OPLBreadcrumb 
			{
                id: breadcrumb
                anchors { top: parent.top; margins: 10; }
                width: (numberedbreadcrumb.text == "" ? parent.width: (parent.width - numberedbreadcrumb.width-20))
                breadcrumbfont :  brdcrumbfont
                breadcrumbfontbold : fontBold  


            }
            
            Text {
                id: numberedbreadcrumb
                anchors.top: parent.top
				anchors.right: parent.right; 
				anchors.rightMargin: 10;
				anchors.topMargin: 10;
                width: text.width
				color: "white"
				font { pixelSize: 20; }
				elide: Text.ElideLeft
                font.family : screenfont
                font.bold : fontBold
            }
            
           Text {
                id: headerinfo
                anchors.top: breadcrumb.bottom
                anchors.topMargin : 2
                width: text.width
                color: "yellow"
				font { pixelSize: 16; }
				elide: Text.ElideLeft
                font.family : screenfont
                font.bold : fontBold
                
            }

            Item {
                id: main
                anchors { top: (headerinfo.text == "" ? breadcrumb.bottom : headerinfo.bottom); left: parent.left; bottom: (footerinfo.text == "" ? softkeys.top : footerinfo.top); right: parent.right; margins: (breadcrumb.text == "" ? 10 : 5); }
                width: parent.width

                Column {
                    anchors.centerIn: parent
                    spacing: 20
                    visible: enableAdjustBar

                    Row {
                        spacing: 10
                        anchors.horizontalCenter: parent.horizontalCenter

                        Image {
                            source: "qrc:/images/left_large.png"
                        }

                        Text {
                            id: progressText
                            text: formatNumber(progressView.value) + unitLabel
                            color: "white"    
                            height: 24  // needs to be same height as arrows so we can center vertically
                            font { pixelSize: 30; weight: Font.Bold}
                            verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignHCenter

                            function formatNumber(number) {
				var tmp;
				console.log("Value is : " + number + " *** step value : " + screen.step);
                                if (screen.step < 1) {
                                    tmp = number.toFixed(1);
                                } else {
                                    tmp = number;
                                }
				if (screen.displayDecimals == true && screen.step >= 1) { tmp = tmp.toFixed(1); }
				console.log("Final formatted value : " + tmp);
				return tmp;
                            }
                        }

                        Image {
                            source: "qrc:/images/right_large.png"
                        }
                    }

                    Row {
                        Rectangle {
                            width: 304; height: 30
                            color: "white"

                            // we have 300px to use from 0% to 100%
                            // a step in px is 300/(max-min)
                            Rectangle {
                                id: progressBar

                                property double pxStep: 300/(screen.maxValue - screen.minValue)
                                width: ((progressView.value * pxStep)- (screen.minValue * pxStep))
                                height: 26
                                x: 2; y: 2
                                color: "#616365"
                            }
                        }
                    }
                }
            }
            
            Text {
                id: footerinfo
                anchors.bottom: softkeys.top
                width: text.width
                anchors.bottomMargin: 5
                color: "yellow"
				font { pixelSize: 16; }
				elide: Text.ElideLeft
                font.family : screenfont
                font.bold : fontBold
                
            }

            SoftkeysWithIcons {
                id: softkeys
                anchors.bottom: parent.bottom

                softkeyIconList: ["", "", "qrc:/images/save-icon.png", "qrc:/images/cancel-icon.png"]
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
                    if (progressView.value < screen.maxValue)
                        progressView.value = screen.checkCurrentValueRange(screen.minValue, screen.maxValue, progressView.value + screen.step)
                    break;
                case Qt.Key_Down:
                    /* fall-through */
                case Qt.Key_Left:
                    /* Decrease progress bar */
                    if (progressView.value > screen.minValue)
                        progressView.value = screen.checkCurrentValueRange(screen.minValue, screen.maxValue, progressView.value - screen.step)
                    break;
                case Qt.Key_F1:
                  if (!event.isAutoRepeat)
                   screen.goBack();
                    break;
                case Qt.Key_F2:
                    // Help
                    //TODO: help not implemented
                    /*if (!event.isAutoRepeat)
                        progressLoader.source = "../NotImplemented.qml"*/
                    break;
                case Qt.Key_F3:
                    // Save value of progress bar
                    if (!event.isAutoRepeat) {
                        screen.valueSaved(progressView.value)
                        screen.goBack();
                    }
                    break;
                case Qt.Key_F4:
                    // Cancel
                    if (!event.isAutoRepeat)
                        screen.goBack();
                    break;
            }

            event.accepted = true
        }
    }
}
