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
        source: "qrc:/subQuestion.jpg"
    }

    Text{
        id: subQuestionText
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 20
        text: "CÂU HỎI PHỤ"
        font.pixelSize: 50
        font.weight: Font.Bold
        color: "white"
    }

    Rectangle{
        id: rectQuestion
        anchors.top: subQuestionText.top
        anchors.topMargin: 208
        anchors.centerIn: parent
        width: 800
        height: 167
        color: "#2e3436"
        anchors.verticalCenterOffset: -155
        anchors.horizontalCenterOffset: 0
        Text{
            id: question
            anchors.centerIn: parent
            text: backEnd.textList[0]
            font.pixelSize: 30
            // warp
            wrapMode: Text.WordWrap
            color: "white"
        }
    }

    Item{
        id: answer1
        anchors.top: rectQuestion.bottom
        anchors.topMargin: 40
        anchors.left: parent.left
        anchors.leftMargin: 100
        Rectangle{
            id: rect1
            width: 200
            height: 50
            color: "black"
            opacity: 1
            border.color: "white"
            border.width: 3
            Text{
                id: textA
                opacity: 1
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: "A"
                font.pixelSize: 30
                color: "white"
            }
        }
        Rectangle{
            id: rectAnswer1
            anchors.top: rect1.bottom
            anchors.topMargin: 0
            anchors.left: rect1.left
            width: rect1.width
            height: 100
            color: "black"
            opacity: 1
            Text{
                id: textAnwser1
                opacity: 1
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: backEnd.textList[1]
                font.pixelSize: 30
                wrapMode: Text.WordWrap
                color: "white"
            }
        }
    }

    Item{
        id: answer2
        anchors.top: rectQuestion.bottom
        anchors.topMargin: 40
        anchors.left: answer1.right
        anchors.leftMargin: 300
        Rectangle{
            id: rect2
            width: 200
            height: 50
            color: "black"
            opacity: 1
            border.color: "white"
            border.width: 3
            Text{
                id: textB
                opacity: 1
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: "B"
                font.pixelSize: 30
                color: "white"
            }
        }
        Rectangle{
            id: rectAnswer2
            anchors.top: rect2.bottom
            anchors.topMargin: 0
            anchors.left: rect2.left
            width: rect2.width
            height: 100
            color: "black"
            opacity: 1
            Text{
                id: textAnwser2
                opacity: 1
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: backEnd.textList[2]
                font.pixelSize: 30
                wrapMode: Text.WordWrap
                color: "white"
            }
        }
    }
    
    Item{
        id: answer3
        anchors.top: rectQuestion.bottom
        anchors.topMargin: 40
        anchors.left: answer2.right
        anchors.leftMargin: 300
        Rectangle{
            id: rect3
            width: 200
            height: 50
            color: "black"
            opacity: 1
            border.color: "white"
            border.width: 3
            Text{
                id: textC
                opacity: 1
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: "C"
                font.pixelSize: 30
                color: "white"
            }
        }
        Rectangle{
            id: rectAnswer3
            anchors.top: rect3.bottom
            anchors.topMargin: 0
            anchors.left: rect3.left
            width: rect3.width
            height: 100
            color: "black"
            opacity: 1
            Text{
                id: textAnwser3
                opacity: 1
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: backEnd.textList[3]
                font.pixelSize: 30
                wrapMode: Text.WordWrap
                color: "white"
            }
        }
    }
   
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
                text: backEnd.textList[4]
                font.pixelSize: 60
                color: "white"
                // Bold
                font.weight: Font.Bold
            }
        }
    }




    Item{

        visible: backEnd.textList[5] !== undefined

        TextField{
            id: guessCharSubQuestion
            x: 408
            y: 572
            width: 255
            height: 50
            placeholderText: "Guess A, B or C"
        }

        Button{
            id: guessButtonSubQuestion
            Text{
                text: "GUESS"
                font.pixelSize: 30
                color: "Black"
                // Bold
                anchors.centerIn: parent
                font.weight: Font.Bold
            }
            x: 436
            y: 653
            width: 200
            height: 50
            onClicked: {
                console.log(guessCharSubQuestion.text)
                backEnd.guessCharSubQuestion(guessCharSubQuestion.text)
            }
        }
    }

    Text{
        id: guessCharSubQuestionNotification
        x: 377
        y: 530
        visible: backEnd.textList[6] !== undefined
        text: backEnd.textList[6]
        font.pixelSize: 20
        color: "white"
        font.weight: Font.Bold
    }
}

/*##^##
Designer {
    D{i:1;invisible:true}
}
##^##*/
