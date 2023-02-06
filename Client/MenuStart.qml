import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item{
    id: menuStart
    anchors.fill: parent
    width: 1024
    height: 768

    BorderImage{
        id: borderImage
        anchors.fill: parent
        source: "qrc:/freefire.jpg"
    }

    TextField{
        id: usernameInput
        anchors.top: parent.top
        anchors.topMargin: 400
        anchors.horizontalCenter: parent.horizontalCenter
        width: 300
        height: 50
        placeholderText: "Nickname"

    }

    Button{
        id: joinButton
        anchors.top: usernameInput.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
        text: "Join"

        onClicked: {
            console.log("Joining game...")
            backEnd.connectToServer()
            backEnd.join(usernameInput.text)
        }

    }
}
