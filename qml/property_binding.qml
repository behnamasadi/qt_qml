import QtQuick 2.12

Rectangle {
    implicitWidth: child.implicitWidth
    implicitHeight: child.implicitHeight
    color:"green";
    //color:"#<alpha><rr><gg><bb>";
    // color: Qt.rgba(0, .05, 0, 1)
    // anchors.centerIn: parent
    width: child.width
    height: child.height
    Image {
        id: child
        source: "../images/PNG_transparency_demonstration_1.png"
        anchors.margins: 5
        anchors.fill: parent
        anchors.centerIn: parent
        width:parent.implicitWidth;
        height:parent.implicitheight;
    }
}
