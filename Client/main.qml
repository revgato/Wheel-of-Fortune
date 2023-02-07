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
            backEnd.exitGame()
            // Close the game

            // Exit the game
            // Qt.quit()
        }

        onWaitingRoom:{
            console.log("Waiting room")
            // Remove the current item
            // stackView.pop()
            stackView.replace("WaitingRoom.qml")
        }

        onRefuse: {
            console.log("Refused")
            stackView.replace("MenuStart.qml")
        }


        onUserJoined: {
            console.log("User joined")
            // stackView.replace("WaitingRoom.qml")
            backEnd.updateWaitingRoom()
        }

        onGameStart:{
            console.log("Game start")
            backEnd.startGame()
        }
       
        onGameState:{
            console.log("Game state")
            stackView.replace("GameState.qml")
        }

        onUpdateGameStateSignal: {
            console.log("Update game state")
            backEnd.updateGameState()        
        }


        onUpdateNotificationSignal:{
            console.log("Update notification")
            backEnd.updateNotification()
        }

        onNotification:{
            console.log("Notification")
            stackView.replace("Notification.qml")
        }

        onUpdateSubQuestionSignal:{
            console.log("Update sub question")
            backEnd.updateSubQuestion()
        }

        onSubQuestion:{
            console.log("Sub question")
            stackView.replace("SubQuestion.qml")
        }
        

        onUpdateEndGameSignal:{
            console.log("Update end game")
            backEnd.updateEndGame()   
        }

        onEndGame:{
            console.log("End game")
            stackView.replace("EndGame.qml")
        }
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
