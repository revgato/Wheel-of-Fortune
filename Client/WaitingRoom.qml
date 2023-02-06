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

    ColumnLayout{
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
    }
}
