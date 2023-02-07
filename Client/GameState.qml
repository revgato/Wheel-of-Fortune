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
        font.weight: Font.Bold
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
        opacity: 1
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

    Rectangle{
        id: rectSector
        y: 605
        anchors.left: parent.left
        anchors.leftMargin: 56
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 45
        width: 227
        height: 118
        color: "#4e9a06"
        opacity: 1
        Text{
            id: sector
            opacity: 1
            anchors.horizontalCenter: rectSector.horizontalCenter
            anchors.verticalCenter: rectSector.verticalCenter
            text: backEnd.textList[1]
            font.pixelSize: 60
            // Bold
            font.weight: Font.Bold
            color: "#2e3436"
        }
    }


    // Text{
    //     id: turn
    //     anchors.left: wheelOfFortuneText.right
    //     anchors.leftMargin: 20
    //     anchors.top: wheelOfFortuneText.bottom
    //     anchors.topMargin: 20
    //     text: "Turn: " + backEnd.textList[2]
    //     font.pixelSize: 20
    //     color: "white"
    // }

    Item{
        id: turn
        anchors.right: parent.right
        anchors.rightMargin: 250
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 170
        Rectangle{
            id: rect1Turn
            width: 200
            height: 50
            color: "#2e3436"
            opacity: 1
            border.color: "white"
            border.width: 3
            Text{
                id: rect1TurnText
                opacity: 1
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: "Current Turn"
                font.pixelSize: 30
                color: "white"
            }
        }
        Rectangle{
            id: rect2Turn
            anchors.top: rect1Turn.bottom
            anchors.topMargin: 0
            anchors.left: rect1Turn.left
            width: rect1Turn.width
            height: 100
            color: "#2e3436"
            opacity: 1
            Text{
                id: rect2TurnText
                opacity: 1
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: backEnd.textList[2]
                font.pixelSize: 60
                color: "white"
                // Bold
                font.weight: Font.Bold
            }
        }
    }

//////////////////////////////

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
            opacity: 1
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
            opacity: 1
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
        anchors.leftMargin: 300
        Rectangle{
            id: rectPlayer1Username
            width: 200
            height: 50
            color: "black"
            opacity: 1
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
            opacity: 1
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
        anchors.leftMargin: 300
        Rectangle{
            id: rectPlayer2Username
            width: 200
            height: 50
            color: "black"
            opacity: 1
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
            opacity: 1
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


    Item{
        id: myTurn
        visible: backEnd.textList[9] == "my_turn" 
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
    Text{
        id: guessCharNotification
        y: 528
        visible: backEnd.textList[10] !== undefined
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: myTurn.top
        anchors.bottomMargin: -562
        text: backEnd.textList[10]
        anchors.horizontalCenterOffset: 18
        font.pixelSize: 20
        color: "white"
        font.weight: Font.Bold 
    }
}
