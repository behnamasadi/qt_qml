import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12




ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "ToolBar Example"

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            ToolButton {
                iconSource: "../images/new.png"
            }
            ToolButton {
                iconSource: "images/open.png"
            }
            ToolButton {
                iconSource: "images/save-as.png"
            }
            Item { 
                Layout.fillWidth: true 
            }
            CheckBox {
                text: "Enabled"
                checked: true
                Layout.alignment: Qt.AlignRight
            }
        }
    }
}