import QtQuick 2.12


Rectangle
{
    visible: true
    width: 400
    height: 400
    Grid
    {
        id:fourColor
        anchors.centerIn: parent
        columns: 2;
        rows:2;

        spacing:10
        visible: false;
        Rectangle
        {
            width:50
            height:50
            color:"red"
        }

        Rectangle
        {
            width:50
            height:50
            color:"black"
        }

        Rectangle
        {
            width:50
            height:50
            color:"blue"
        }

        Rectangle
        {
            width:50
            height:50
            color:"yellow"
        }
    }


    ListModel
    {
        id:nameModel
        ListElement{XnameX: "dweda"; age:2}
        ListElement{XnameX: "r3r4b"; age:4}
        ListElement{XnameX: "f34fc"; age:5}
        ListElement{XnameX: "f34fd"; age:1}
        ListElement{XnameX: "f34fe"; age:7}
    }




    Grid
    {
        rows : 5;
        columns: 5;
        spacing: 10;
        anchors.centerIn: parent
        Repeater
        {
            //model:8
            model:nameModel
            delegate: Rectangle
            {
                width:70;
                height:70;
                color:"lightgreen"
                Text
                {
                    text:model.XnameX
                    anchors.centerIn: parent
                }

            }
        }


    }

}

