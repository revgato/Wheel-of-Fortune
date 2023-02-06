extern "C"
{
#include "utils.h"
}
#include "backend.h"

extern conn_msg_type conn_msg;
extern char username[50];

QString Backend::text = "";
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

    if (conn_msg.type == WAITING_ROOM)
    {
        // Assign username to char*
        for (int i = 0; i < conn_msg.data.waiting_room.joined; i++)
        {
            Backend::text = QString::fromStdString(conn_msg.data.waiting_room.player[0].username);
            emit textChanged();
        }
        emit waitingRoom();
    }
    else
    {
        emit refuse();
    }
}

QString Backend::getText() const
{
    return Backend::text;
}

void Backend::setText(QString text)
{
    Backend::text = text;
}
