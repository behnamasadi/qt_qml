import QtQuick 2.12

Rectangle {
    width: _aSize.width
    height: _aSize.height

    Column {
        anchors.centerIn: parent
        spacing: 10
        Text {
            text: _currentuser.name
        }
        Text {
            text: _currentuser.age
        }
        Text {
            text: _currentuser.role
        }
    }
}
