import QtQuick 2.12

Rectangle
{
    width: _aSize.width;
    height: _aSize.height;
    MouseArea
    {
        anchors.fill:parent
        //https://youtu.be/quFciLDIxUw?list=PL6CJYn40gN6hdNC1IGQZfVI707dh9DPRc&t=843
        onClicked:
        {
            //accessing a global gadget
            console.log("global lookup", _santa);

            // return a gadget from c++
            var santa=_db.lookPerson("fake santa");


            // return a gadget back to c++
            _db.addPerson(_db.makePerson("Jesper",18));

            //updating a gadget
        }
    }

    Column
    {
        anchors.centerIn: parent;
        spacing:10;
        Text
        {
            text:_aString;
        }
    }

    Column
    {
        anchors.centerIn: parent;
        spacing:10;
        Text
        {
            text:_currentuser.name;
        }
        Text
        {
            text:_currentuser.age;
        }
        Text
        {
            text:_currentuser.role;
        }

    }
}

