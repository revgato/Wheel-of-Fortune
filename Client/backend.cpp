extern "C"
{
#include "utils.h"
}
#include "backend.h"

extern conn_msg_type conn_msg;
extern char username[50];

// QString Backend::text = "";
QStringList Backend::textList;
char Backend::server_ip[16];
int Backend::server_port = 5500;

Backend::Backend(QObject *parent) : QObject(parent)
{
}

void Backend::connectToServer()
{
    if (connect_to_server(Backend::server_ip, Backend::server_port) == 1)
    {
        emit connectedToServer();
    }
    else
    {
        emit connectionFailed();
    }
}

void Backend::join(QString username_input)
{
    strcpy(username, username_input.toStdString().c_str());
    conn_msg.data.player = init_player(username, -1);
    conn_msg.type = JOIN;
    send_server();
    receive_server();
    pthread_t tid;

    if (conn_msg.type == WAITING_ROOM)
    {
        for(int i=0; i<conn_msg.data.waiting_room.joined; i++)
        {
            textList.append(conn_msg.data.waiting_room.player[i].username);
        }
        // Backend::text = QString::fromStdString(conn_msg.data.waiting_room.player[0].username);
        emit waitingRoom();
    }
    else
    {
        emit refuse();
    }
    pthread_create(&tid, NULL, &pthread_waiting_room, NULL);
    // Wait for the thread to finish
    // pthread_join(tid, NULL);
    // emit gameStart();
}

void *pthread_waiting_room(void *arg)
{
    free(arg);
    pthread_detach(pthread_self());
    while (conn_msg.data.waiting_room.joined != PLAYER_PER_ROOM){
        receive_server();
        if (conn_msg.type == WAITING_ROOM){
            printf("New player joined\n");
        }
    }
    printf("All players joined\n");
    // emit Backend::gameStart();
    pthread_cancel(pthread_self());
}

QStringList Backend::getTextList() const
{
    return textList;
}
