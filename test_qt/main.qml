import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import dientului.Backend 1.0

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    property bool isSignedIn: false

    Backend{
        id: myBackend
        onLoginSuccess: {
            console.log("onLoginSuccess")
            root.isSignedIn = true
            myBackend.status = ""
        }
        onLoginFail: {
            console.log("onLoginFail")
            root.isSignedIn = false
        }
    }

    Column{
        visible: !isSignedIn
        anchors.centerIn: parent
        spacing: 10
        TextField{
            id: userNameInput
            placeholderText: "Username"
            width: parent.width
        }
        TextField{
            id: passwordInput
            placeholderText: "Password"
            echoMode: TextInput.Password
            width: parent.width
        }
        Button{
            id: signInButton
            text: "Sign In"
            width: 200
            height: 80
            onClicked: {
//                root.isSignedIn = true
                myBackend.login(userNameInput.text, passwordInput.text)
                console.log("Button clicked")
            }
        }
        Label{
            text: myBackend.status
        }
    }
    Column{
        visible: isSignedIn
        anchors.centerIn: parent
        Label{
            text: "Sign in success"
        }
        Button{
            id: signOutButton
            width: 200
            height: 80
            text: "Sign Out"
            onClicked: {
                root.isSignedIn = false
            }
        }
    }
}
