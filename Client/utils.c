#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "game.h"
#include "communicate.h"
#include <ctype.h>
#include "utils.h"

conn_data_type conn_data;
conn_msg_type conn_msg;
char username[50];
char guess_char;
int client_sock;    
struct sockaddr_in server_addr;
int bytes_sent, bytes_received, sin_size;

int connect_to_server(char *server_ip, int server_port)
{
    // Step 1: Construct a TCP socket
    if ((client_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        // Call socket() to create a socket
        perror("\nError: ");
        return 0;
    }

    // Step 2: Define the address of the server
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);
    // printf("Server IP: %s - Port: %d\n", server_ip, server_port);

    // Step 3: Request to connect server
    if (connect(client_sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) < 0)
    {
        printf("\nError!Can not connect to sever! Client exit imediately! ");
        return 0;
    }

    return 1;
}

int disconnect_from_server()
{
    close(client_sock);
    return 1;
}

void send_server(){
    bytes_sent = send(client_sock, &conn_msg, sizeof(conn_msg), 0);
    printf("[DEBUG] Send %d bytes\n", bytes_sent);
    if (bytes_sent < 0)
    {
        printf("Error: Cannot send message to server!\n");
        exit(1);
    }
}


