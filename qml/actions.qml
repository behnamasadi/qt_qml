import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 1.4

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "QML Application"
    property bool newActionActivated: false

    function newDocument() {
        console.log("Creating a new document...")
        // Implement new document creation logic here
        newActionActivated = !newActionActivated // Toggle the activation state
    }

    function openDocument() {
        console.log("Opening a document...")
        //fileDialog.open() // Opens the dialog to select a file
    }

    function saveDocument() {
        console.log("Saving the current document...")
        // Implement document save logic here
    }

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

    // Define actions for New, Open, and Save
    Action {
        id: newAction
        text: "&New"
        shortcut: StandardKey.New
        iconSource: newActionActivated ? "qrc:/images/new_active.png" : "qrc:/images/new.png"
        onTriggered: newDocument()
    }

    //    toolBar: ToolBar {
    //        RowLayout {
    //            anchors.fill: parent
    //            anchors.margins: spacing
    //            ToolButton {
    //                action: newAction
    //            }
    //            ToolButton {
    //                iconSource: "qrc:/images/open.png"
    //                onClicked: openDocument()
    //            }
    //            ToolButton {
    //                iconSource: "qrc:/images/save.png"
    //                onClicked: saveDocument()
    //            }
    //            Item {
    //                Layout.fillWidth: true
    //            }
    //            CheckBox {
    //                text: "Enabled"
    //                checked: true
    //                Layout.alignment: Qt.AlignRight
    //            }
    //        }
    //    }
    TabView {
        id: tabView
        anchors.fill: parent
        Tab {
            title: "Red"
            Rectangle {
                color: "red"
            }
        }
        Tab {
            title: "Blue"
            Rectangle {
                color: "blue"
            }
        }
        Tab {
            title: "Green"
            Rectangle {
                color: "green"

                anchors.fill: parent

                ToolBar {
                    id: greenToolBar
                    Layout.fillWidth: true
                    anchors.top: parent.top
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
            }
        }
    }

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
        Menu {
            title: "&Edit"
            visible: tabView.currentIndex == 2
            MenuItem {
                action: cutAction
            }
            MenuItem {
                action: copyAction
            }
            MenuItem {
                action: pasteAction
            }
        }
        Menu {
            title: "&Help"
            MenuItem {
                text: "About..."
                //onTriggered: aboutDialog.open()
            }
        }
    }
}
