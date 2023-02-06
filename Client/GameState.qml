import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item{
    id: gameState
    anchors.fill: parent
    width: 1024
    height: 768

    BorderImage{
        id: borderImage
        anchors.fill: parent
        source: "qrc:/freefire.jpg"
    }

    Text{
        id: crossWord
        anchors.centerIn: parent
        text: backEnd.textList[0]
        font.pixelSize: 70
        color: "white"
    }

    Text{
        id: player0
        anchors.top: parent.top
        anchors.topMargin: 20
        text: backEnd.textList[1] + " : " + backEnd.textList[2]
        font.pixelSize: 90
        color: "white"
    }

    Text{
        id: player1
        anchors.top: parent.top
        anchors.topMargin: 120
        text: backEnd.textList[3] + " : " + backEnd.textList[4]
        font.pixelSize: 90
        color: "white"
    }
}
