import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12




/*
ApplicationWindow is a Window that adds convenience for positioning items, such as MenuBar, ToolBar, and StatusBar
 in a platform independent manner.
That is, it is an item that inherits from Window but has certain default attributes, it is similar to
QMainWindow with respect to QWidget.
*/
ApplicationWindow {
    width: 800
    height: 600
    visible: true
    title: qsTr("foo")

    //signal clicked

    //color: tapHandler.pressed ? "goldenrod" : hoverHandler.hovered ? "wheat" : "beige"
    Text {
        id: txt1
        text: qsTr("txt1")
        x: 400
        y: 400

        MouseArea {
            anchors.fill: parent // the defaul size is 0x0 so we have to set fill parnet
            onPressed: parent.color = "red"
            onReleased: parent.color = "green"
            onClicked: txt1.font.bold = !txt1.font.bold
            acceptedButtons: Qt.RightButton
        }
    }

    Text {
        anchors.top: txt1.bottom
        anchors.right: txt1.right
        id: txt2
        text: qsTr("txt2")
        //property binidng, if txt2MouseArea.pressed is rtue
        color: txt2MouseArea.pressed ? "green" : "red"

        //color: txt2MouseArea.clicked ? "green": "red"
        MouseArea {
            id: txt2MouseArea
            anchors.fill: parent
        }

        width: 100
        height: 2 * width
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Open")
                onTriggered: console.log("foo foo")
            }
            MenuItem {
                text: qsTr("close")
                onTriggered: Qt.quit()
            }
        }

        Menu {
            title: qsTr("Edit")
        }
    }

    Button {
        id: btn1
        text: qsTr("click me")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width: txtInput1.width
        //height: txtInput1.height;
    }

    ColumnLayout {
        spacing: 0
        Rectangle {
            id: rect1
            color: "red"
            width: 100
            height: 100
        }
        Rectangle {
            id: rect2
            color: "blue"
            width: 100
            height: 100
        }

        TapHandler {
            onTapped: switch (point.modifiers) {
                      case Qt.ControlModifier | Qt.AltModifier:
                          console.log("CTRL+ALT")
                          break
                      case Qt.ControlModifier | Qt.AltModifier | Qt.MetaModifier:
                          console.log("CTRL+META+ALT")
                          break
                      default:
                          console.log("other modifiers", point.modifiers)
                          break
                      }
        }
    }

    Item {

        anchors.top: btn1.bottom
        anchors.right: btn1.right
        TextInput {
            id: txtInput1

            text: "complete me"
        }
    }
}
