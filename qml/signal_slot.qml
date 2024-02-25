import QtQuick 2.12

Rectangle {
    width: 600
    height: 800

        Connections {
            target: _currentuser
            function onRoleChanged(message) {
                currentuser_role.text = message
            }
        }



    Column {
        anchors.centerIn: parent
        spacing: 10
        Text {
            id: currentuser_name
            text: _currentuser.name
        }
        Text {
            id: currentuser_age
            text: _currentuser.age
        }
        Text {
            id: currentuser_role
            text: _currentuser.role
        }
    }
}
