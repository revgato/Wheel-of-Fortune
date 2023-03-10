import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item{
    id: waitingRoom
    width: 1024
    height: 768

    BorderImage{
        id: borderImage
        anchors.fill: parent
        source: "qrc:/waitingRoom.jpg"
    }

    Text{
        id: waitingRoomText
        text: "PHÒNG CHỜ"
        font.pixelSize: 50
        color: "white"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 50
    }

    ColumnLayout{
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: waitingRoomText.bottom
        anchors.topMargin: 30
        
        // Beautiful text boxes containing usernames
        Rectangle{
            id: username0Box
            width: 300
            height: 50
            color: "black"
            radius: 10
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 50

            Text{
                id: username0
                text: backEnd.textList[0]
                font.pixelSize: 30
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Rectangle{
            id: username1Box
            visible: backEnd.textList[1] !== undefined
            width: 300
            height: 50
            color: "black"
            radius: 10
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: username0Box.bottom
            anchors.topMargin: 50

            Text{
                id: username1
                text: backEnd.textList[1]
                font.pixelSize: 30
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Rectangle{
            id: username2Box
            visible: backEnd.textList[2] !== undefined
            width: 300
            height: 50
            color: "black"
            radius: 10
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: username1Box.bottom
            anchors.topMargin: 50

            Text{
                id: username2
                text: backEnd.textList[2]
                font.pixelSize: 30
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }
}
