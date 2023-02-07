import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item{
    id: gameStateMyTurn
    
    // ---------GameState.qml----------
    BorderImage{
        id: borderImage
        anchors.fill: parent
        source: "qrc:/freefire.jpg"
    }

    Text{
        id: wheelOfFortuneText
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 20
        text: "Wheel of Fortune"
        font.pixelSize: 50
    }
    Rectangle{
        id: rectCrossWord
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: wheelOfFortuneText.bottom
        anchors.topMargin: 20
        width: backEnd.textList[0].length * 70
        height: 100
        color: "red"
        Text{
            id: crossWord
            anchors.horizontalCenter: rectCrossWord.horizontalCenter
            text: backEnd.textList[0]
            font.pixelSize: 70
            color: "white"
        }
    }

    
    Text{
        id: sector
        anchors.left: rectCrossWord.right
        anchors.leftMargin: 20
        anchors.top: wheelOfFortuneText.bottom
        anchors.topMargin: 20
        text: "Sector: " + backEnd.textList[1]
        font.pixelSize: 20
        color: "white"
    }


    Text{
        id: turn
        anchors.left: sector.right
        anchors.leftMargin: 20
        anchors.top: wheelOfFortuneText.bottom
        anchors.topMargin: 20
        text: "Turn: " + backEnd.textList[2]
        font.pixelSize: 20
        color: "white"
    }

    Text{
        id: player0
        anchors.top: rectCrossWord.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        text: backEnd.textList[3] + " : " + backEnd.textList[4]
        font.pixelSize: 90
        color: "white"
    }

    Text{
        id: player1
        anchors.top: player0.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        text: backEnd.textList[5] + " : " + backEnd.textList[6]
        font.pixelSize: 90
        color: "white"
    }

    Text{
        id: player2
        anchors.top: player1.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        visible: backEnd.textList[7] !== undefined
        text: backEnd.textList[7] + " : " + backEnd.textList[8]
        font.pixelSize: 90
        color: "white"
    }

    // ---------GameState.qml----------

    TextField{
        id: guessChar
        anchors.horizontalCenter: player2.horizontalCenter
        anchors.top: player2.bottom
        anchors.topMargin: 20
        width: 200
        height: 50
        placeholderText: "Guess a character"
    }

    Button{
        id: guessButton
        enabled: guessChar.text.length > 0
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: guessChar.bottom
        anchors.bottomMargin: 20
        width: 5 * 30
        height: 50

        Text{
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Guess"
            color: "black"
            font.pixelSize: 30
        }

        onClicked: {
            console.log(guessChar.text)
            backEnd.guessChar(guessChar.text)
        }
    }
}
