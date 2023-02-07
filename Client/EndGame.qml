import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item{
    id: endGame
    anchors.fill: parent
    width: 1024
    height: 768

    BorderImage{
        id: borderImage
        anchors.fill: parent
        source: "qrc:/summary.jpg"
    }

    Text{
        id: endGameText
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 20
        text: "TỔNG KẾT"
        font.pixelSize: 50
        font.weight: Font.Bold
        color: "white"
    }
    Rectangle{
        id: rectCrossWord
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 150
        width: backEnd.textList[0].length * 45
        height: 100
        color: "#2e3436"
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


//////////////////////////////

    Item{
        id: player0
        anchors.top: rectCrossWord.bottom
        anchors.topMargin: 30
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
                text: backEnd.textList[1]
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
                text: backEnd.textList[2]
                font.pixelSize: 30
                color: "white"
            }
        }
    }

    Item{
        id: player1
        anchors.top: rectCrossWord.bottom
        anchors.topMargin: 30
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
                text: backEnd.textList[3]
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
                text: backEnd.textList[4]
                font.pixelSize: 30
                color: "white"
            }
        }
    }

    Item{
        id: player2
        anchors.top: rectCrossWord.bottom
        anchors.topMargin: 30
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
                text: backEnd.textList[5]
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
                text: backEnd.textList[6]
                font.pixelSize: 30
                color: "white"
            }
        }
    }

    Rectangle{
        width: parent.width
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 100
        // anchors.horizontalCenter: parent.horizontalCenter
        height: 100
        color: "#2e3436"
        Text{
            id: textWinner
            width: 720
            // height: 300
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.centerIn: parent
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.WordWrap
            text: "Winner: " + backEnd.textList[7]
            font.pixelSize: 40
            font.weight: Font.Bold

            color: "white"
        }

    }
    
}
