import QtQuick 1.0

Rectangle {
    id: screen
    width: 480
    height: 272

    default property alias content: stack.children

    property alias backGroundColor: view.color
    property alias statusText: statusBar.titleText

    property alias breadcrumb: breadcrumb.text
    property alias softKeyTextList: softkeys.softkeyTextList

    property alias btnText1: softkeys.btnText1
    property alias btnText2: softkeys.btnText2
    property alias btnText3: softkeys.btnText3
    property alias btnText4: softkeys.btnText4

    property alias source: viewLoader.source
    property alias item: viewLoader.item

    property int stackMargin: 5

    signal goBack()

    Loader {
        id: viewLoader
        anchors.fill: parent
        source: ""

        onSourceChanged: {
            if (source == "") {
                view.visible = true
                view.focus = true
            } else {
                viewLoader.focus = true
            }
        }
        onLoaded: view.visible = false;
    }

    Connections {
        target: viewLoader.item
        onGoBack: {
            viewLoader.source = "";
            view.visible = true
            view.focus = true
        }
    }

    Rectangle {
        id: view
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
                id: stack
                anchors { top: (breadcrumb.text == "" ? statusBar.bottom : breadcrumb.bottom); left: parent.left; bottom: softkeys.top; right: parent.right; margins: screen.stackMargin; }
            }

            Softkeys {
                id: softkeys
                anchors.bottom: parent.bottom

                softkeyTextList: ["", "", "", ""]
            }
        }

        focus: true
        Keys.forwardTo: parent
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
                        break;
                    case Qt.Key_F3:
                        break;
                    case Qt.Key_F4:
                        break;
                }
            }

            event.accepted = true
        }
    }
}
