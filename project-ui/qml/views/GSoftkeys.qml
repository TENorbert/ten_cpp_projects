import QtQuick 1.0

Item {
    id: container
    width: parent.width; height: btn1.height + hr.height + 5

    property variant softkeyTextList: ["", "", "", ""]

    property alias btnText1: btn1.text
    property alias btnText2: btn2.text
    property alias btnText3: btn3.text
    property alias btnText4: btn4.text

    property alias btn1_font: btn1.font
    property alias btn2_font: btn2.font
    property alias btn3_font: btn3.font
    property alias btn4_font: btn4.font

    Rectangle {
        id: hr
        width: 0; height: 0
        //width: parent.width; height: 2
        anchors { bottom: buttons.top; bottomMargin: 5; }
        //color: "#616365"
    }

    Item {
        id: buttons
        width: parent.width; height: btn1.height
        anchors.bottom: parent.bottom

        TextButton {
            id: btn1
            text: softkeyTextList[0]
            x: 7
        }

        TextButton {
            id: btn2
            text: softkeyTextList[1]
            x: 122
        }

        TextButton {
            id: btn3
            text: softkeyTextList[2]
            x: 238
        }

        TextButton {
            id: btn4
            text: softkeyTextList[3]
            x: 354
        }
    }
}
