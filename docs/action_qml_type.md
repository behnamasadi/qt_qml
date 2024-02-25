# Action QML Type
In applications many common commands can be invoked via menus, toolbar buttons, and keyboard shortcuts. An action can be bound to a menu item and a toolbar button, and it will automatically keep them in sync. For example, in a word processor, if the user presses a Bold toolbar button, the Bold menu item will automatically be checked.


Action represents an abstract user interface action that can have shortcuts and can be assigned to menu items and toolbar buttons.

`QtQuick` Controls supports actions in `Button`, `ToolButton`, and `MenuItem`.

Actions may contain text, an icon, and a shortcut. Actions are normally triggered by the user via menu items, toolbar buttons, or keyboard shortcuts:


```
Action {
    id: copyAction
    text: qsTr("&Copy")
    icon.name: "edit-copy"
    shortcut: StandardKey.Copy
    onTriggered: window.activeFocusItem.copy()
}
```



## Signals
### toggled

### triggered

Refs: [1](https://doc.qt.io/qt-5/qml-qtquick-controls-action.html#details)


[source](../src/actions.cpp)
