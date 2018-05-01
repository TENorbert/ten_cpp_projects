import QtQuick 1.0
import com.ecolab.components 1.0

Rectangle {
    id: screen
    anchors.fill: parent

    default property alias content: main.children

    property alias breadcrumb: breadcrumb.text
	property alias numberedbreadcrumb: numberedbreadcrumb.text
	property alias headertext: headerinfo.text
	property alias footertext: footerinfo.text

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
    
    property bool menuHighlightVisible : true

    signal goBack()
    signal enterPressed(int currentIndex)

    function reloadFontProperties()
    {
        //console.log("************Inside reloadFontProperties*******");
        
        screen.screenfont = (isTMScreen==true)? AquanomicsLM.GetTMLangaugeFontName() : AquanomicsLM.GetTMLangaugeFontName()
        headerinfofont = (setEntireScreenSameFont==true) ? screenfont: overrideheaderinfofont
        numberedbreadcrumbfont = (setEntireScreenSameFont==true) ? screenfont: overridenumberedbreadcrumbfont
        footerinfofont = (setEntireScreenSameFont==true) ? screenfont: overridefooterinfofont
       
        screen.fontBold = (isTMScreen==true)? AquanomicsLM.GetTMLangaugeFontBoldStatus() : false
        brdcrumbfont =  (setEntireScreenSameFont==true) ? screenfont: overridebrdcrumbfont
        //console.log("************DONE*******");
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
            
            Text  Text.ElideLeft {
                id: numberedbreadcrumb
                anchors.top: parent.top
                anchors.right: parent.right;
                anchors.rightMargin: 15;
                width: text.width
                font.family : numberedbreadcrumbfont
                font.bold : fontBold
                color: "white"
                font { pixelSize: 20; }
                elide:
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
                anchors.bottomMargin: (footerinfo.text == "" ? 1 : (headerinfo.text == "") ? 5: 9)   
                width: parent.width

                /* The menu */
                ListView {
                    id: menu
                    anchors { fill: parent; }
                    //model: menuModelTest
                    delegate: menuDelegate
                    highlight: menuHighlight
                    spacing: 2
                    clip: true

                    Keys.onReturnPressed: {
                        if (!event.isAutoRepeat) {
                            screen.enterPressed(menu.currentIndex)
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
                    //anchors.centerIn: parent
                    text: "No list elements!"
                    color: "white"
                    font.pixelSize: 20
                    visible: menu.count == 0
                    wrapMode: Text.WordWrap
                    width: parent.width

                }

                Component {
                    id: menuDelegate

                    Item {
                        id: wrapper
                        width: menuText.width; height: menuText.height + 10
                        x: 10

                        Text {
                            id: menuText
                            font.pixelSize: 20
                            anchors.verticalCenter: parent.verticalCenter
                            text: name
                            color: "white"
                            font.family : screenfont
                            font.bold : fontBold
                        }
                    }
                }

                Component {
                    id: menuHighlight

                    Rectangle {
                        color: "#616365"
                        radius: 5
                        width: menu.width; height: menu.currentItem.height
						visible : menuHighlightVisible

                        /* up/down arrows */
                        Rectangle {
                            anchors { right: parent.right; rightMargin: 5; }
                            width: 25; height: parent.height
                            color: parent.color

                            Image {
                                id: arrowImage
                                anchors.centerIn: parent
                                source: "qrc:/images/arrows.png"
                            }

                            states: [
                                State {
                                    when: (menu.currentIndex == 0)&&(menu.currentIndex != (menu.count - 1))
                                    PropertyChanges { target: arrowImage; source: "qrc:/images/arrow_down.png"; }
                                },
                                State {
                                    when: menu.currentIndex == (menu.count - 1)&&(menu.currentIndex != 0)
                                    PropertyChanges { target: arrowImage; source: "qrc:/images/arrow_up.png"; }
                                }
                            ]
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
                font.family : footerinfofont
                font.bold : fontBold
                
            }
            

            SoftkeysWithIcons {
                id: softkeys
                anchors.bottom: parent.bottom

                softkeyIconList: ["", "", "", "qrc:/images/help-icon.png"]
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
                    	{
                        screen.goBack();
                        }
                        break;
                    case Qt.Key_F2:
                        break;
                    case Qt.Key_F3:;
                        break;
                    case Qt.Key_F4:
                        {
                            screen.source ="qrc:/qml//Help.qml"
                            event.accepted = true
                        }
                        
                        break;
                }
            }

            event.accepted = true
        }
    }
}
