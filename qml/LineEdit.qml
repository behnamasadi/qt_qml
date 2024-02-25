import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12

Rectangle
{
    //property string text: childInputText.text
    //property string text: ""
    property alias text: childInputText.text
    readonly property int area: width*height

    function clear()
    {
        text=""
    }

    implicitHeight: childInputText.implicitHeight;
    implicitWidth: childInputText.implicitWidth;
    border.color: "green"
    radius:4;
    smooth: true;
    clip: true;
    color: "white";
    TextInput
    {
        id: childInputText;
        //text: "Enter text..."
        text:parent.text;
        opacity: 0.5;
        anchors.fill: parent;
        anchors.margins: 2
        color:  focus ? "black" : "gray"
        font.pixelSize:parent.height -4;

    }
}


