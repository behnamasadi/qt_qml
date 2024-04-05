import QtQuick 2.12
import QtQuick.Window 2.12

import QtQuick.Layouts 1.12
import QtQuick.Controls 1.4
ApplicationWindow
{
    height:600
    width:800

 Action {
        id: copyAction
        text: "&Copy"
        shortcut: StandardKey.Copy
        iconName: "edit-copy"
        enabled: (!!activeFocusItem && !!activeFocusItem["copy"])
        onTriggered: activeFocusItem.copy()
    }

    Action {
        id: cutAction
        text: "Cu&t"
        shortcut: StandardKey.Cut
        iconName: "edit-cut"
        enabled: (!!activeFocusItem && !!activeFocusItem["cut"])
        onTriggered: activeFocusItem.cut()
    }

    Action {
        id: pasteAction
        text: "&Paste"
        shortcut: StandardKey.Paste
        iconName: "edit-paste"
        enabled: (!!activeFocusItem && !!activeFocusItem["paste"])
        onTriggered: activeFocusItem.paste()
    }

    toolBar: ToolBar {
        RowLayout {
            anchors.fill: parent
            anchors.margins: spacing
            Label {
                text: UI.label
            }

            ToolButton {
                iconSource: "../images/new.png"
            }
            ToolButton {
                iconSource: "../images/open.png"
            }
            ToolButton {
                iconSource: "../images/save-as.png"
            }
            Item { 
                Layout.fillWidth: true 
            }
            CheckBox {
                text: "Enabled"
                checked: true
                Layout.alignment: Qt.AlignRight
            }



            Item { Layout.fillWidth: true }
            CheckBox {
                id: enabler
                text: "Enabled"
                checked: true
            }
        }
    }

    menuBar: MenuBar {
        Menu {
            title: "&File"
            MenuItem {
                text: "E&xit"
                shortcut: StandardKey.Quit
                onTriggered: Qt.quit()
            }
        }
        Menu {
            title: "&Edit"
            visible: tabView.currentIndex == 2
            MenuItem { action: cutAction }
            MenuItem { action: copyAction }
            MenuItem { action: pasteAction }
        }
        Menu {
            title: "&Help"
            MenuItem {
                text: "About..."
                onTriggered: aboutDialog.open()
            }
        }
    }

}