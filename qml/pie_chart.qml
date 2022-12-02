import Charts 1.0
import QtQuick 2.12

Item {
    width: 300
    height: 300

    PieChart {
        id: chartA
        anchors.top: parent.top
        anchors.left: parent.left
        width: 100
        height: 100
        name: "chartA"
        //color: "red"
        color: chartB.color

        //ChartCleared is a signal so it can be called
        onChartCleared: console.log("The chart has been cleared")
    }

    Text {
        anchors {
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
            bottomMargin: 20
        }
        text: chartA.name
    }

    MouseArea {
        anchors.fill: chartA
        //clearChart() can be called because of Q_INVOKABLE. we call ChartCleared signal in clearChart()
        onClicked: chartA.clearChart()
    }

    PieChart {
        id: chartB
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        width: 100
        height: 100
        name: "chart B"
        color: "blue"
        onColorChanged: console.log("The chart color has been changed")
    }

    MouseArea {
        anchors.fill: chartB
        //setColor() can be called because of Q_INVOKABLE. we call ChartCleared signal in clearChart()
        onClicked: chartB.setColor("yellow")
    }
}
