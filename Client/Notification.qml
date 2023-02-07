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
        source: "qrc:/notification.jpg"
    }
    Rectangle{
        width: parent.width
        anchors.top: parent.top
        anchors.topMargin: 300
        // anchors.horizontalCenter: parent.horizontalCenter
        height: 360
        color: "#2e3436"
        Text{
            id: textNotification
            width: 720
            // height: 300
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.WordWrap
            text: backEnd.textList[0]
            font.pixelSize: 40

            color: "white"
        }

    }
}
