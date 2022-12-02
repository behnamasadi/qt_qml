import QtQuick 2.12

Text {
    id: msgid
    width: 800
    height: 600
    text: msg.text // invokes Message::text() to get this value

    Component.onCompleted: {
        msg.text = "haha" // invokes Message::setText()
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            var result = msg.postMessage("Hello from QML")
            console.log("Result of postMessage():", result)
            msg.refresh()
        }
    }
}
