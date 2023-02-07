import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item{
    id: subQuestion
    anchors.fill: parent
    width: 1024
    height: 768

    BorderImage{
        id: borderImage
        anchors.fill: parent
        source: "qrc:/freefire.jpg"
    }

    Text{
        id: question
        anchors.centerIn: parent
        text: backEnd.textList[0]
        font.pixelSize: 70
        color: "white"
    }

    Text{
        id: answer1
        anchors.top: parent.top
        anchors.topMargin: 20
        text: "A. " + backEnd.textList[1]
        font.pixelSize: 90
        color: "white"
    }

    Text{
        id: answer2
        anchors.top: parent.top
        anchors.topMargin: 120
        text: "B. " + backEnd.textList[2]
        font.pixelSize: 90
        color: "white"
    }

    Text{
        id: answer3
        anchors.top: parent.top
        anchors.topMargin: 220
        text: "C. " + backEnd.textList[3]
        font.pixelSize: 90
        color: "white"
    }
}