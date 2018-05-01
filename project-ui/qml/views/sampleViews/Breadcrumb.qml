import Qt 4.7

Item {
    id: breadcrumb
    height: menuBreadcrumb.height

    property alias text: menuBreadcrumb.text

    Text {
        id: menuBreadcrumb
        width: parent.width
        text: ""
        color: "white"
        font { pixelSize: 20; }
        elide: Text.ElideLeft
    }
}
