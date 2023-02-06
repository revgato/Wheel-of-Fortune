extern "C"{
    #include "utils.h"
}
#include "backend.h"

std::string Backend::server_ip = "127.0.0.1";
int Backend::server_port = 5500;

Backend::Backend(QObject *parent) : QObject(parent)
{
}

void Backend::connectToServer(){
    char ip[16];
    strcpy(ip, Backend::server_ip.c_str());
    if(connect_to_server(ip, Backend::server_port) == 1){
        emit connectedToServer();
    } else{
        emit connectionFailed();
    }
}