import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item{
    id: waitingRoom
    width: 1024
    height: 768

    property bool show_username0: false
    property bool show_username1: false

    BorderImage{
        id: borderImage
        anchors.fill: parent
        source: "qrc:/freefire.jpg"
    }

    // ColumnLayout{
        Text{
            id: username0
            visible: show_username0
            text: backEnd.text
            font.pixelSize: 30
            color: "white"
            
        }

        // Text{
        //     id: username1
        //     visible: false
        //     text: backEnd.text
        //     font.pixelSize: 30
        //     color: "white"
        // }
    // }
}
