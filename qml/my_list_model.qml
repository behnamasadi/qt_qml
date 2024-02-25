import QtQuick 2.12
import QtQuick.Controls 2.12
import com.example 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "ListView Example"

    // Use the myListModel object as the model for the ListView
    ListView {
        anchors.fill: parent
        model: myListModel

    

    Component.onCompleted: {

        myListModel.addItem(1, "baz");
        myListModel.addItem(2, "qux");

            // Example of calling setData
            myListModel.setData(0, 30, MyListModel.IDRole); // set the ID of the first item to 30

            // Example of calling insertRows
            myListModel.insertRows(1, 1); // insert one row at position 1

            // Example of calling removeRows
            myListModel.removeRows(2, 1); // remove one row at position 2
    }

        // Define the delegate to display each item
        delegate: Item {
            width: parent.width
            height: 50

            Row {
                spacing: 10
                Text {
                    text: "ID: " + ID
                }
                Text {
                    text: "First Name: " + firstName
                }
            }
        }
    }
}