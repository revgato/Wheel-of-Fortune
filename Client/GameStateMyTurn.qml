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

    TextField{
        id: guessChar
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        width: 200
        height: 50
        placeholderText: "Guess a character"
    }

    Button{
        id: guessButton
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: guessChar.top
        anchors.bottomMargin: 20
        width: 200
        height: 50
        onClicked: {
            console.log(guessChar.text)
            backEnd.guessChar(guessChar.text)
        }
    }
}
