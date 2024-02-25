import QtQuick 2.12


Text
{
    width:400
    height:400
    text:msg.author
    Component.onCompleted:
    {
        msg.author="new name"
    }
}


