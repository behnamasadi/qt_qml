import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")


    Rectangle
    {
        id:rect1;
        width: 100;
        height:50;
        color: "red";
        anchors.centerIn: parent;
    }

    Rectangle
    {
        id:rect2;
        width: 100;
        height:100;
        color: "blue";
        anchors.top: rect1.bottom ;
        anchors.left: rect1.right ;
        radius: 5
    }



    onWidthChanged:
    {
           // Will be executed after window.width value changes.
        back_qml.changeValue(1);
        btn1.scale=btn1.scale/ 1.3
    }

    onHeightChanged:
    {
           // Will be executed after window.height value changes.
           back_qml.changeValue(2);

           btn1.text  = "xx"
           btn1.scale=btn1.scale* 1.3
    }

    Label
    {
        id:label
        x:22
        y:88
        width:355
        height:62
        text: qsTr("lable")

        Connections
        {
            target: back_qml
            onValueChanged: label.text=s;
        }
    }


    Button {

        id: btn1
        x: 47
        y: 229
        text: "btn1"
        scale: 1.3
        onClicked: back_qml.changeValue(1);
    }
    Button {
        id: btn2
        x: 163
        y: 229
        text: "btn2"
        scale: 1.3
        onClicked: back_qml.changeValue(2);
    }

    Button {
        id: btn3
        x: 163
        y: 329
        text: "btn3"
        width: btn1.width+btn2.width
        onClicked: back_qml.changeValue(2);
    }

}

