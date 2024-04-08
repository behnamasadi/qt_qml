# Action QML Type
In applications many common commands can be invoked via menus, toolbar buttons, and keyboard shortcuts. An action can be bound to a menu item and a toolbar button, and it will automatically keep them in sync. For example, in a word processor, if the user presses a Bold toolbar button, the Bold menu item will automatically be checked.


Action represents an abstract user interface action that can have shortcuts and can be assigned to menu items and toolbar buttons.

`QtQuick` Controls supports actions in `Button`, `ToolButton`, and `MenuItem`.

Actions may contain text, an icon, and a shortcut. Actions are normally triggered by the user via menu items, toolbar buttons, or keyboard shortcuts:

define the action for opening new document:
```
Action {
	id: newAction
	text: "&New"
	shortcut: StandardKey.New
	iconSource: newActionActivated ? "qrc:/images/new_active.png" : "qrc:/images/new.png"
	onTriggered: newDocument()
}
```

Tool bar button for opening new document:

```
 toolBar: ToolBar {
        RowLayout {
            anchors.fill: parent
            anchors.margins: spacing
            ToolButton {
                action: newAction
            }
            ToolButton {
                iconSource: "qrc:/images/open.png"
                onClicked: openDocument()
            }
            ToolButton {
                iconSource: "qrc:/images/save.png"
                onClicked: saveDocument()
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
```

Menu bar for opening new document:
```
    menuBar: MenuBar {
        Menu {
            title: "&File"

            MenuItem {
                action: newAction
            }

            MenuItem {
                text: "&Open"
                shortcut: StandardKey.Open
                onTriggered: openDocument()
            }
            MenuItem {
                text: "&Save"
                shortcut: StandardKey.Save
                onTriggered: saveDocument()
            }
            MenuItem {
                text: "E&xit"
                shortcut: StandardKey.Quit
                onTriggered: Qt.quit()
            }
        }
        
    }
```

Define a function for opening new document:

```
 property bool newActionActivated: false

    function newDocument() {
        console.log("Creating a new document...")
        // Implement new document creation logic here
        newActionActivated = !newActionActivated // Toggle the activation state
    }
```



Refs: [1](https://doc.qt.io/qt-5/qml-qtquick-controls-action.html#details)


[source](../src/actions.cpp)
