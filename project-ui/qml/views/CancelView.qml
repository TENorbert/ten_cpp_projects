import Qt 4.7

import com.ecolab.components 1.0

Rectangle {
    id: screen
    anchors.fill: parent

    //default property alias content: main.children

    property alias customerName: breadcrumb.text
	property alias washerNo: washerImage.source
	property alias cancelImage: cancelimage.source
	property alias formulaText:formulatext.text
	property alias formulaType:formulatype.text
	
    property alias softKeyIconList: softkeys.softkeyIconList

    property alias btnIcon1: softkeys.btnIcon1
    property alias btnIcon2: softkeys.btnIcon2
    property alias btnIcon3: softkeys.btnIcon3
    property alias btnIcon4: softkeys.btnIcon4
    property alias source: cancelLoader.source

   signal goBack()
	onGoBack: console.log("back")
	function back() {
		console.log("function back")
		screen.goBack()
	}
    Loader {
        id: cancelLoader
        anchors.fill: parent
        source: ""
        onSourceChanged: cancelLoader.focus = true
        onLoaded: cancelView.visible = false;
    }
    Connections {
        target: cancelLoader.item
        onGoBack: {
            cancelLoader.source = "";
            cancelView.visible = true
            cancelView.focus = true
			console.log("cancelView : Back signal slot");
        }
    }

  
    Rectangle {
        id: cancelView
        anchors.fill: parent
        color: "#0082c8"

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

            Item {
                id: main
                anchors { left: parent.left; bottom: softkeys.top; right: parent.right;}
				anchors.top: (breadcrumb.text == "" ? parent.top : breadcrumb.bottom)
                anchors.topMargin: 5
                width: parent.width

                Column {
                    spacing: 10
                        Row {
							spacing: 10
							Image {
								id:washerImage
								width:60
								height:70
                            }
							Image {
								id:cancelimage
								width:70
								height:70
							}
                        }

                        Text {
                            id: formulatext
							font.pixelSize: 20
							color: "white"
							text: ""
                        }
						Text {
                            id: formulatype
							font.pixelSize: 20
							color: "white"
							text: ""
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
                case Qt.Key_F1:
				screen.goBack();
				console.log("Emitting goback signal from cancel view ");
                    break;
                case Qt.Key_F2:
                    break;
                case Qt.Key_F3:
                    break;
                case Qt.Key_F4:
                {
                    screen.source = "../Help.qml"
                    event.accepted = true
                }break;
            }

            event.accepted = true
        }
    }
}
