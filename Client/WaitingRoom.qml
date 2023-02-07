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
        source: "qrc:/freefire.jpg"
    }

    Text{
        id: waitingRoomText
        text: "Waiting Room"
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
        Text{
            id: username0
            text: backEnd.textList[0]
            font.pixelSize: 30
            color: "white"
        }

        Text{
            id: username1
            text: backEnd.textList[1]
            font.pixelSize: 30
            color: "white"
        }

        Text{
            id: username2
            text: backEnd.textList[2]
            font.pixelSize: 30
            color: "white"
        }
    }
}
