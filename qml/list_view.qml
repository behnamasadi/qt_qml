import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle {
    width: 150
    height: 200

    ListModel {
        id: contact_list
        ListElement {
            first_name: "Foo"
            last_name: " Wise"
            phone: 1111
        }
        ListElement {
            first_name: "Fee"
            last_name: "Smith"
            phone: 2222
        }
        ListElement {
            first_name: "Bar"
            last_name: "Brown"
            phone: 3333
        }
    }

    Component
    {
        id:contactDelegate
        Item
        { width: 200; height: 20
            Column{
                Text{
                    text: first_name+ ","+last_name
                    Component.onCompleted: console.log("start:", model.first_name, model.index)
                    Component.onDestruction: console.log("end:", model.first_name, model.index)

                    MouseArea {
                        anchors.fill: parent //by default is zero pixel;
                        onClicked: my_contact_list_view.currentIndex = index
                    }
                }
            }
        }
    }

    ListView
    {
        id: my_contact_list_view
        anchors.fill: parent
        model: contact_list
        delegate: contactDelegate
        clip: true
        cacheBuffer: 10 //pixel lines
        onCurrentIndexChanged: console.log(currentIndex)

    }
}
