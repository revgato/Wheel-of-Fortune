import QtQuick 2.0
import QtQuick.Controls 2.12
import Backend 1.0


ApplicationWindow{
    id: rootWindow
    visible: true
    width: 1024
    height: 720
    maximumWidth: 1024
    maximumHeight: 720
    minimumWidth: 1024
    minimumHeight: 720
    title: "Wheel of Fortune"

    screen: Qt.application.screens[0]
    x: screen.virtualX + (screen.width - width) / 2
    y: screen.virtualY + (screen.height - height) / 2


    Backend{
        id: backEnd

        onConnectedToServer: {
            console.log("Connected to server")
        }

        onConnectionFailed: {
            console.log("Connection failed")
        }

        onWaitingRoom:{
            console.log("Waiting room")
            stackView.push("WaitingRoom.qml")
        }

        onRefuse: {
            console.log("Refused")
        }

        onTextChanged: {
            console.log("Text changed")
            waitingRoom.show_username0 = true
        }

        // onW
    }

    Button{
        id: startBtn
        width: 320
        height: 240
        anchors.centerIn: parent
    }

    StackView{
        id: stackView
        anchors.fill: parent
        initialItem: MenuStart{

        }
    }

    // Handle user click exit
    onClosing: {
        // backEnd.disconnectFromServer()
        console.log("Exit game")
    }
}
