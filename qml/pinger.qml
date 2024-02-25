import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Rectangle {
    width: 800
    height: 600
    visible: true

    Label {
        id: os
        text: "The host type is:" + _OS + " "
    }

    Label {
        id: machineToPing
        text: "Machine to Ping:"
        anchors.top: os.bottom
    }

    TextEdit {
        id: machineToPingTxt
        text: "4.2.2.4"
        //text: "/checknow"
        anchors.left: machineToPing.right
        anchors.top: machineToPing.top
        //        MouseArea {
        //            anchors.fill: parent
        //            onClicked: {
        //                machineToPingTxt.text = ""
        //            }
        //        }
    }

    Button {
        id: start
        text: "start"
        //anchors.left: machineToPingTxt.right
        anchors.top: machineToPing.bottom
        anchors.margins: 5

        onClicked: {
            _pinger.setAddress(machineToPingTxt.text)
            _pinger.start()
        }
    }

    Button {
        id: stop
        text: "stop"
        anchors.left: start.right
        anchors.top: machineToPing.bottom
        anchors.margins: 5
        onClicked: {

            _pinger.stop()
        }
    }

    Label {
        id: pingResult
        text: "Ping Result:"

        Connections {
            target: _pinger
            function onOutput(message) {
                pingResult.text = message
            }
        }

        anchors.centerIn: parent
    }
}
