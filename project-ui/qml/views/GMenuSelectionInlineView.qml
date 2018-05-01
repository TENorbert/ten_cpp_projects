import QtQuick 1.0
import com.ecolab.components 1.0

Rectangle {
    id: screen
    anchors.fill: parent

    default property alias content: main.children

    property alias breadcrumb: breadcrumb.text
    property alias numberedbreadcrumb: numberedbreadcrumb.text

    property alias softKeyIconList: softkeys.softkeyIconList
    property alias btnIcon1: softkeys.btnIcon1
    property alias btnIcon2: softkeys.btnIcon2
    property alias btnIcon3: softkeys.btnIcon3
    property alias btnIcon4: softkeys.btnIcon4

    property alias menuModel: menu.model
    property alias menuDelegate: menu.delegate
    property alias menuHighlight: menu.highlight
    property alias currentIndex: menu.currentIndex

    property alias errorText: errorText.text
    property alias source: menuLoader.source
    property alias item: menuLoader.item

    signal valueSaved()
    signal goBack()

    property bool setEntireScreenSameFont : true
    property bool isTMScreen : true
    property variant overridebrdcrumbfont: ""
    property variant overrideheaderinfofont: ""
    property variant overridenumberedbreadcrumbfont: ""
    property variant overridefooterinfofont: ""
    property variant screenfont: (isTMScreen==true)? AquanomicsLM.GetTMLangaugeFontName() : AquanomicsLM.GetPrimaryLangaugeFontName()
    property variant headerinfofont : (setEntireScreenSameFont==true) ? screenfont: overrideheaderinfofont
    property variant brdcrumbfont : (setEntireScreenSameFont==true) ?  screenfont : ""
    property variant numberedbreadcrumbfont : (setEntireScreenSameFont==true) ? screenfont: overridenumberedbreadcrumbfont
    property variant footerinfofont : (setEntireScreenSameFont==true) ? screenfont: overridefooterinfofont
    property bool fontBold : (isTMScreen==true)? AquanomicsLM.GetTMLangaugeFontBoldStatus() : false
    
        function reloadFontProperties()
    {
        console.log("************Inside reloadFontProperties*******");
        
        screen.screenfont = (isTMScreen==true)? AquanomicsLM.GetTMLangaugeFontName() : AquanomicsLM.GetTMLangaugeFontName()
        headerinfofont = (setEntireScreenSameFont==true) ? screenfont: overrideheaderinfofont
        numberedbreadcrumbfont = (setEntireScreenSameFont==true) ? screenfont: overridenumberedbreadcrumbfont
        footerinfofont = (setEntireScreenSameFont==true) ? screenfont: overridefooterinfofont
       
        screen.fontBold = (isTMScreen==true)? AquanomicsLM.GetTMLangaugeFontBoldStatus() : false
        brdcrumbfont =  (setEntireScreenSameFont==true) ? screenfont: overridebrdcrumbfont
        console.log("************DONE*******");
        
    }
    

    Loader {
        id: menuLoader
        anchors.fill: parent
        source: ""

        onSourceChanged: menuLoader.focus = true
        onLoaded: menuView.visible = false;
    }
    Connections {
        target: menuLoader.item
        onGoBack: {
            menuLoader.source = "";
            reloadFontProperties();
            menuView.visible = true
            menuView.focus = true
        }
    }

    Rectangle {
        id: menuView
        anchors.fill: parent
        color: "#0082c8"

        Item {
            id: container
            anchors { fill: parent; margins: 10; }

            OPLBreadcrumb {
                id: breadcrumb
                anchors.top: parent.top
                width: (numberedbreadcrumb.text == "" ? parent.width: (parent.width - numberedbreadcrumb.width-20))
                breadcrumbfont :  brdcrumbfont
                breadcrumbfontbold : fontBold  

            }
            
	    Text {
                id: numberedbreadcrumb
                anchors.top: parent.top
                anchors.right: parent.right;
                anchors.rightMargin: 15;
                width: text.width
                color: "white"
                font { pixelSize: 20; }
                elide: Text.ElideLeft
                font.family : numberedbreadcrumbfont
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
                font.family : headerinfofont
                font.bold : fontBold
                
            }
            
            Item {
                id: main
                anchors { left: parent.left; right: parent.right;  }
                anchors.top: (headerinfo.text == "" ? breadcrumb.bottom : headerinfo.bottom)
                anchors.topMargin: (headerinfo.text == "" ? 10 : 9)
                anchors.bottom : (footerinfo.text == "" ? softkeys.top : footerinfo.top)
                anchors.bottomMargin: (footerinfo.text == "" ? 1 : 9)   
                width: parent.width

                /* The menu */
                ListView {
                    id: menu
                    anchors { fill: parent; }
                    delegate: menuDelegate
                    highlight: menuHighlight
                    spacing: 2
                    clip: true

                    Keys.onLeftPressed: {
                        if (menu.currentItem) {
                            var index = menu.currentIndex
                            var idx = menuModel.get(index).idx
                            if (idx > 0)
                                menuModel.setProperty(index, "idx", idx - 1)
                            event.accepted = true
                        }
                    }

                    Keys.onRightPressed: {
                        if (menu.currentItem) {
                            var index = menu.currentIndex
                            var idx = menuModel.get(index).idx
                            if (idx < (menuModel.get(index).attributes.count - 1))
                                menuModel.setProperty(index, "idx", idx + 1)
                            event.accepted = true
                        }
                    }

		    Component.onCompleted: positionViewAtIndex(currentIndex, ListView.Contain)
                }

                /*
                    Text to display if no elements are present in the list.
                    This can be overridden by setting the top-level errorText property alias.
                */
                Text {
                    id: errorText
                    anchors.centerIn: parent
                    text: "No list elements!"
                    color: "white"
                    font.pixelSize: 20
                    visible: menu.count == 0
                }

                Component {
                    id: menuDelegate

                    Item {
                        id: wrapper
                        width: parent.width
                        height: menuText.height + 10

                        Text {
                            id: menuText
                            font.pixelSize: 20
                            anchors { verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: 10; }
                            text: name 
                            color: "white"
                        }

                        /* Left Arrow */
                        Image {
                            id: leftArrow
                            anchors.right: optionText.left
                            anchors.rightMargin: 10
                            anchors.verticalCenter: parent.verticalCenter
                            source: "qrc:/images/left_arrow.png"
                            visible: wrapper.ListView.isCurrentItem && idx > 0
                        }

                        Text {
                            id: optionText
                            font.pixelSize: 20
                            anchors { verticalCenter: parent.verticalCenter; right: rightArrow.left; rightMargin: 10; }
                            text: attributes.get(idx).option
                            color: "white"
                            font.family : screenfont
                            font.bold : fontBold
                        }

                        /* Right Arrow */
                        Image {
                            id: rightArrow
                            anchors.right: parent.right
                            anchors.rightMargin: 5
                            anchors.verticalCenter: parent.verticalCenter
                            source: "qrc:/images/right_arrow.png"
                            visible: wrapper.ListView.isCurrentItem && idx < (attributes.count - 1)
                        }
                    }
                }

                Component {
                    id: menuHighlight

                    Rectangle {
                        color: "#616365"
                        radius: 5
                        width: menu.width; height: menu.currentItem.height
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
                font.family : footerinfofont
                font.bold : fontBold
            }

            SoftkeysWithIcons {
                id: softkeys
                anchors.bottom: parent.bottom

                softkeyIconList: ["", "", "qrc:/images/save-icon.png", "qrc:/images/cancel-icon.png"]
            }
        }

        focus: true
        Keys.forwardTo: [parent, menu]
        Keys.onPressed: {
            /* disable auto repeat */
            if (!event.isAutoRepeat) {
                switch (event.key) {
                    case Qt.Key_Up:
                        break;
                    case Qt.Key_Right:
                        break;
                    case Qt.Key_Down:
                        break;
                    case Qt.Key_Left:
                        break;
                    case Qt.Key_F1:
                        break;
                    case Qt.Key_F2:
                        // Help
                        // TODO: help not implemented
                        //menuLoader.source = "../NotImplemented.qml"
                        break;
                    case Qt.Key_F3:;
                        // Save current selection
                        //screen.valueSaved(curentSelection);
                        screen.valueSaved();
                        screen.goBack();
                        break;
                    case Qt.Key_F4:
                        // Cancel
                        screen.goBack();
                        break;
                }
            }

            event.accepted = true
        }
    }
}
