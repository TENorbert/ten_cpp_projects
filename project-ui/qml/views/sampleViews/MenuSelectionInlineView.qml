import Qt 4.7

import "../components"

Rectangle {
    id: screen
    anchors.fill: parent

    default property alias content: main.children

    property alias breadcrumb: breadcrumb.text

    property alias softKeyTextList: softkeys.softkeyTextList
    property alias btnText1: softkeys.btnText1
    property alias btnText2: softkeys.btnText2
    property alias btnText3: softkeys.btnText3
    property alias btnText4: softkeys.btnText4

    property alias menuModel: menu.model

    property alias errorText: errorText.text

    signal valueSaved()

    signal goBack()

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
            menuView.visible = true
            menuView.focus = true
        }
    }

    property int machineTypeIndex: 0
    property int operatingModeIndex: 1

    Rectangle {
        id: menuView
        anchors.fill: parent
        color: "#0082c8"

        Item {
            id: container
            anchors { fill: parent; margins: 10; }

            StatusBar {
                id: statusBar
                anchors.top: parent.top
            }

            Breadcrumb {
                id: breadcrumb
                anchors { top: statusBar.bottom; margins: 5 }
                width: parent.width
            }

            Item {
                id: main
                anchors { left: parent.left; right: parent.right; bottom: softkeys.top; }
                anchors.top: (breadcrumb.text == "" ? statusBar.bottom : breadcrumb.bottom)
                anchors.topMargin: (breadcrumb.text == "" ? 10 : 5)
                anchors.bottomMargin: (breadcrumb.text == "" ? 10 : 9)

                /* The menu */
                ListView {
                    id: menu
                    anchors { fill: parent; }
                    delegate: menuDelegate
                    highlight: menuHighlight
                    spacing: 2

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
                            text: name + ": "
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

            Softkeys {
                id: softkeys
                anchors.bottom: parent.bottom

                softkeyTextList: ["", "", "Save", "Cancel"]
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
