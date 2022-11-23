import QtQuick 2.12

Rectangle {
    width: 600
    height: 800

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
