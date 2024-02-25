
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


ApplicationWindow {
    width: 800
    height: 600
    visible: true
    title: qsTr("foo")

Slider {
    id: foo
    from: 1
    value: 25
    to: 100
    onMoved:
    {
        console.log(foo.value)
    }
}
}

