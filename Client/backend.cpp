extern "C"{
    #include "utils.h"
}
#include "backend.h"

extern conn_msg_type conn_msg;
extern char username[50];


char Backend::server_ip[16];
int Backend::server_port = 5500;

Backend::Backend(QObject *parent) : QObject(parent)
{
}

void Backend::connectToServer(){
    if(connect_to_server(Backend::server_ip, Backend::server_port) == 1){
        emit connectedToServer();
    } else{
        emit connectionFailed();
    }
}

void Backend::join(QString const username_input){
    strcpy(username, username_input.toStdString().c_str());
    conn_msg.data.player = init_player(username, -1);
    conn_msg.type = JOIN;
    send_server();
    receive_server();

    if(conn_msg.type == WAITING_ROOM){
        emit waitingRoom();
    } else{
        emit refuse();
    }
}
