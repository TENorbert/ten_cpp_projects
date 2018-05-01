import Qt 4.7

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
    property alias softKeyTextList: softkeys.softkeyTextList

    property alias btnText1: softkeys.btnText1
    property alias btnText2: softkeys.btnText2
    property alias btnText3: softkeys.btnText3
    property alias btnText4: softkeys.btnText4

    signal valueSaved(double value)
    signal valueUpdated(double value)

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

            StatusBar {
                id: statusBar
                anchors.top: parent.top
            }

            Breadcrumb {
                id: breadcrumb
                anchors { top: statusBar.bottom; margins: 5; }
                width: parent.width
            }

            Item {
                id: main
                anchors { top: breadcrumb.bottom; left: parent.left; bottom: softkeys.top; right: parent.right; margins: (breadcrumb.text == "" ? 10 : 5); }
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
                                if (screen.step < 1) {
                                    return number.toFixed(1)
                                } else {
                                    return number
                                }
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

            Softkeys {
                id: softkeys
                anchors.bottom: parent.bottom

                softkeyTextList: ["", "", "Save", "Cancel"]
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
