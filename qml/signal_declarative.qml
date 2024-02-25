import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12

ApplicationWindow
{
    visible: true;

    Item
    {
        width:300;
        height: 200;


        Rectangle
        {
            color:"green";
            anchors.fill: parent

            CheckBox
            {

                checked: true;
                onCheckedChanged : checked  ?  parent.color="red": parent.color="blue";
                //onChecked: checkValue ?  parent.color:"red": parent.color:"blue";
            }
        }

    }

    Rectangle
    {
        id:traficLight
        color:"black";
        width:50;
        height:150
        anchors.centerIn: parent
        Rectangle
        {
            id:red;
            radius:50;
            color:"red";
            x:0;
            y:0;
            width:50;
            height:50;

        }

        Rectangle
        {
            id:green;
            radius:50;
            color:"green";
            x:0;
            y:50;
            width:50;
            height:50;

        }

        Rectangle
        {
            id:yellow;
            radius:50;
            color:"yellow";
            x:0;
            y:100;
            width:50;
            height:50;

        }

    }
    Timer
    {
        interval: 1000;
        repeat: true;
        running:true;
        //onTriggered:
    }



}
