import QtQuick 2.12


/*
To receive a notification when a particular signal is emitted for a particular object,
the object definition should declare a signal handler named:
 on<Signal>, where <Signal> is the name of the signal, with the first letter capitalized.
The signal handler should contain the JavaScript code to be executed when the signal handler is invoked.


*/
Rectangle {
    width: 600
    height: 800
    MouseArea {
        anchors.fill: parent
        onClicked: {
            // return a gadget back to c++
            _db.addPerson(_db.makePerson("Behnam", 18))

            // return a gadget from c++
            var behnam = _db.lookPerson("behnam")

            //accessing a global gadget
            //console.log("global lookup", behnam.name)
            //console.log(behnam.name)

            //updating a gadget
        }
    }
}
