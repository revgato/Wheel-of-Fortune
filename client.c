#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
// #include <pthread.h>
#include "game.h"
#include "communicate.h"

void print_title()
{
    printf("Wheel of Fortune\n");
    printf("====================================\n\n");
}

void print_waiting_room(waiting_room_type waiting_room)
{
    // Clear screen
    printf("\033[2J");

    // Print title
    print_title();

    // Print waiting room
    printf("Waiting room:\n");
    for (int i = 0; i < waiting_room.slot; i++)
    {
        printf("Player %d: %s\n", i + 1, waiting_room.player[i].username);
    }
    printf("\n");
}

int main()
{
    int client_sock;
    struct sockaddr_in server_addr;
    int bytes_sent, bytes_received, sin_size;

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
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    printf("Server IP: %s - Port: %d\n", SERVER_ADDR, SERVER_PORT);

    // Step 3: Request to connect server
    if (connect(client_sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) < 0)
    {
        printf("\nError!Can not connect to sever! Client exit imediately! ");
        return 0;
    }

    // Step 4: Communicate with server
    // Step 4.1: Send username to server

    printf("Welcome to Wheel of Fortune\n");

    printf("Please enter your username: ");
    char username[50];
    scanf("%s", username);
    player_type player = init_player(username, -1);

    printf("Connecting to server...\n");
    // Init communicate message
    conn_msg_type conn_msg = make_conn_msg(JOIN, player);

    // Send message to server
    bytes_sent = send(client_sock, &conn_msg, sizeof(conn_msg), 0);
    if (bytes_sent <= 0)
    {
        perror("\nError: ");
        close(client_sock);
        return 0;
    }

    // Step 4.2: Infinitely receive message from server
    while (1)
    {
        bytes_received = recv(client_sock, &conn_msg, sizeof(conn_msg), 0);
        if (bytes_received <= 0)
        {
            perror("\nError: ");
            close(client_sock);
            return 0;
        }

        // Handle message from server
        switch (conn_msg.type)
        {
        case JOIN:
            // TODO: Handle join message
            break;
        case WAITING_ROOM:
            // TODO: Handle waiting room message
            print_waiting_room(conn_msg.waiting_room);
            break;
        case GAME_STATE:
            // TODO: Handle game state message
            break;
        }
    }

    // Step 5: Close socket
    close(client_sock);
    return 0;
}
