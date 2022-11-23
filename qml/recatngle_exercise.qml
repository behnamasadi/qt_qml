import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12


ApplicationWindow
{
    visible: true
    width:400
    height:400

    Rectangle
    {
        id:mainrect;
//        width:400
//        height:400
        anchors.fill: parent
        clip:true;
       // opacity: 0.5
    }

    Rectangle
    {
        id:smalltoprect;
        width:toprect.width/2;
        height:toprect.height/2;
        color:"red"
        x:50;
        y:50;
        z:2;
        opacity: 0.5

    }

    Rectangle
    {
        id:toprect;
        width:mainrect.width
        height:mainrect.height/2
        color:"lightblue"


    }

    Rectangle
    {
        id:bottomrect;
        width:mainrect.width
        height:mainrect.height/2
        color:"green"
        anchors.top: toprect.bottom
        anchors.margins: 50

        Image
        {
            source: "images/HQ.png";
            x:10
            y:10
            z:1
            width:sourceSize.width*2;
            height:sourceSize.height*2;
            Component.onCompleted: console.log(width, height, sourceSize);
            clip:true;
            onStateChanged: console.log("");
            opacity: 0.5;
            scale:2.0
            rotation:45
            transformOrigin: Item.TopLeft
        }

    }


}



