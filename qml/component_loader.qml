import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

ApplicationWindow
{
    visible: true;
    LineEdit
    {
        id:lineEdit
        text: "Enter text..."
    }
    Text {
        anchors.top: lineEdit.bottom
        id: txtFromLineEdit
        text: "summery "+lineEdit.text;
    }
}
