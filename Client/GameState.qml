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
        source: "qrc:/gameState.jpg"
    }

    Text{
        id: wheelOfFortuneText
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 20
        text: "CHIẾC NÓN KỲ DIỆU"
        font.pixelSize: 50
        color: "white"
    }
    Rectangle{
        id: rectCrossWord
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: wheelOfFortuneText.bottom
        anchors.topMargin: 50
        width: backEnd.textList[0].length * 45
        height: 100
        color: "black"
        opacity: 0.5
        Text{
            id: crossWord
            opacity: 1
            anchors.horizontalCenter: rectCrossWord.horizontalCenter
            anchors.verticalCenter: rectCrossWord.verticalCenter
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

    // Text{
    //     id: player0
    //     anchors.top: rectCrossWord.bottom
    //     anchors.topMargin: 20
    //     anchors.left: parent.left
    //     anchors.leftMargin: 20
    //     text: backEnd.textList[3] + " : " + backEnd.textList[4]
    //     font.pixelSize: 90
    //     color: "white"
    // }

    // 2 rectangle. 1 rectangle for player0 username, 1 rectangle for player0 score
    Item{
        id: player0
        anchors.top: rectCrossWord.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 100
        Rectangle{
            id: rectPlayer0Username
            width: 200
            height: 50
            color: "black"
            opacity: 0.5
            border.color: "white"
            border.width: 3
            Text{
                id: player0Username
                opacity: 1
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: backEnd.textList[3]
                font.pixelSize: 30
                color: "white"
            }
        }
        Rectangle{
            id: rectPlayer0Score
            anchors.top: rectPlayer0Username.bottom
            anchors.topMargin: 0
            anchors.left: rectPlayer0Username.left
            width: rectPlayer0Username.width
            height: 100
            color: "black"
            opacity: 0.5
            Text{
                id: player0Score
                opacity: 1
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: backEnd.textList[4]
                font.pixelSize: 30
                color: "white"
            }
        }
    }

    Item{
        id: player1
        anchors.top: rectCrossWord.bottom
        anchors.topMargin: 20
        anchors.left: player0.right
        anchors.leftMargin: 350
        Rectangle{
            id: rectPlayer1Username
            width: 200
            height: 50
            color: "black"
            opacity: 0.5
            border.color: "white"
            border.width: 3
            Text{
                id: player1Username
                opacity: 1
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: backEnd.textList[5]
                font.pixelSize: 30
                color: "white"
            }
        }
        Rectangle{
            id: rectPlayer1Score
            anchors.top: rectPlayer1Username.bottom
            anchors.topMargin: 0
            anchors.left: rectPlayer1Username.left
            width: rectPlayer1Username.width
            height: 100
            color: "black"
            opacity: 0.5
            Text{
                id: player1Score
                opacity: 1
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: backEnd.textList[6]
                font.pixelSize: 30
                color: "white"
            }
        }
    }

    Item{
        id: player2
        anchors.top: rectCrossWord.bottom
        anchors.topMargin: 20
        anchors.left: player1.right
        anchors.leftMargin: 600
        Rectangle{
            id: rectPlayer2Username
            width: 200
            height: 50
            color: "black"
            opacity: 0.5
            border.color: "white"
            border.width: 3
            Text{
                id: player2Username
                opacity: 1
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: backEnd.textList[7]
                font.pixelSize: 30
                color: "white"
            }
        }
        Rectangle{
            id: rectPlayer2Score
            anchors.top: rectPlayer2Username.bottom
            anchors.topMargin: 0
            anchors.left: rectPlayer2Username.left
            width: rectPlayer2Username.width
            height: 100
            color: "black"
            opacity: 0.5
            Text{
                id: player2Score
                opacity: 1
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: backEnd.textList[8]
                font.pixelSize: 30
                color: "white"
            }
        }
    }

    // Text{
    //     id: player1
    //     anchors.top: player0.bottom
    //     anchors.topMargin: 20
    //     anchors.left: parent.left
    //     anchors.leftMargin: 20
    //     text: backEnd.textList[5] + " : " + backEnd.textList[6]
    //     font.pixelSize: 90
    //     color: "white"
    // }

    // Text{
    //     id: player2
    //     anchors.top: player1.bottom
    //     anchors.topMargin: 20
    //     anchors.left: parent.left
    //     anchors.leftMargin: 20
    //     visible: backEnd.textList[7] !== undefined && backEnd.textList[7] !== "my_turn"
    //     text: backEnd.textList[7] + " : " + backEnd.textList[8]
    //     font.pixelSize: 90
    //     color: "white"
    // }

    Item{
        id: myTurn
        visible: backEnd.textList[7] == "my_turn" || backEnd.textList[9] == "my_turn" 
        TextField{
            id: guessChar
            x: 408
            y: 572
            width: 255
            height: 50
            placeholderText: "Guess a character"
        }

        Button{
            id: guessButton
            enabled: guessChar.text.length > 0
            anchors.horizontalCenter: guessChar.horizontalCenter
            anchors.top: guessChar.bottom
            anchors.topMargin: 20
            width: 200
            height: 50
            

            Text{
                anchors.centerIn: parent
                text: "GUESS"
                color: "black"
                font.pixelSize: 30
                font.weight: Font.Bold
            }

            onClicked: {
                console.log(guessChar.text)
                backEnd.guessChar(guessChar.text)
            }
        }
    }
}
