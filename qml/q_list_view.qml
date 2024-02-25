import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import com.mycompany.qmlcomponents 1.0

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("currentIndex: %1").arg(listView.currentIndex)

    ListView {
        id: listView
        anchors.fill: parent
        anchors.margins: 10
        model: Students {}

        delegate: RowLayout {
            width: listView.width

            TextField {
                text: model.name
                horizontalAlignment: Text.AlignHCenter

                Layout.preferredWidth: 1
                Layout.fillWidth: true

                onAccepted: model.name = text
            }

            Text {
                text: model.age

                Layout.preferredWidth: 1
                Layout.fillWidth: true

                horizontalAlignment: Text.AlignHCenter
            }
        }
    }

    footer: RowLayout {
        Button {
            text: qsTr("Append")
            onClicked: listView.model.append()
        }
        Button {
            text: qsTr("Remove last")
            onClicked: listView.model.removeLast()
        }
        Button {
            text: qsTr("Clear")
            onClicked: listView.model.clear()
        }
    }
}
