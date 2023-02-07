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

    Item{

        visible: backEnd.textList[4] !== undefined

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
}

/*##^##
Designer {
    D{i:1;invisible:true}D{i:2;invisible:true}D{i:3;invisible:true}D{i:4;invisible:true}
D{i:5;invisible:true}
}
##^##*/
