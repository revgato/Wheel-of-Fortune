import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import "GameState.qml" as GameState

Item{
    id: gameStateMyTurn
    // GameState{
        
    // }

    TextField{
        id: guessChar
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: header.bottom
        anchors.topMargin: 20
        width: 200
        height: 50
        placeholderText: "Guess a character"
    }

    Button{
        id: guessButton
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: guessChar.bottom
        anchors.bottomMargin: 20
        width: 200
        height: 50
        onClicked: {
            console.log(guessChar.text)
            backEnd.guessChar(guessChar.text)
        }
    }
}
