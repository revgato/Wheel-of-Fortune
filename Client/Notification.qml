import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item{
    id: notification
    width: 1024
    height: 768

    BorderImage{
        id: borderImage
        anchors.fill: parent
        source: "qrc:/freefire.jpg"
    }

    Text{
        id: textNotification
        width: 720
        height: 200
        // wrapMode: Text.WordWrap
        anchors.centerIn: parent
        text: backEnd.textList[0]
        font.pixelSize: 50
        color: "white"
    }
}
