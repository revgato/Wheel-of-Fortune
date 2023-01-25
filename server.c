#include <stdio.h> /* These are the usual header files */
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "game.h"
#include "communicate.h"

// Global variables
client_room_type client_room;

// Handle client tasks
void *client_handle(void *arg);

int main()
{
    int listenfd, *connfd;
    struct sockaddr_in server, *client; // Server's address information
    int sin_size;
    pthread_t tid;
    int bytes_received, bytes_sent;
    int current_joined;

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    { /* calls sockets() */
        perror("\nError: ");
        return 0;
    }

    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY); /* INADDR_ANY puts your IP address automatically */

    if (bind(listenfd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        perror("\nError: ");
        return 0;
    }

    if (listen(listenfd, BACKLOG) == -1)
    {
        perror("\nError: ");
        return 0;
    }

    sin_size = sizeof(struct sockaddr_in);
    client = malloc(sin_size);

    while (1)
    {
        client_room_type client_room = init_client_room();
        waiting_room_type waiting_room = init_waiting_room();
        current_joined = 0;

        // Waiting for client to connect (3 clients)
        while (current_joined < PLAYER_PER_ROOM -2)
        {
            if ((client_room.connfd[current_joined] = accept(listenfd, (struct sockaddr *)client, &sin_size)) == -1)
                perror("\nError: ");
            printf("You got a connection from %s\n", inet_ntoa((*client).sin_addr)); /* Print client's IP */

            // Create new conn_msg variable
            conn_msg_type conn_msg;

            // TODO: Receive username from client
            bytes_received = recv(client_room.connfd[current_joined], &conn_msg, sizeof(conn_msg), 0);
            if (bytes_received < 0)
            {
                perror("\nError: ");
                return 0;
            }
            strcpy(client_room.username[current_joined], conn_msg.data.player.username);
            strcpy(waiting_room.player[current_joined].username, conn_msg.data.player.username);

            client_room.joined++;
            waiting_room.joined++;

            // TODO: Send waiting room to client
            copy_waiting_room_type(&conn_msg.data.waiting_room, waiting_room);
            conn_msg = make_conn_msg(WAITING_ROOM, conn_msg.data);
            // printf("Waiting room joined: %d\n", waiting_room.joined);
            // bytes_sent = send(client_room.connfd[current_joined], &conn_msg, sizeof(conn_msg_type), 0);
            send_all(client_room, conn_msg);
            if (bytes_sent < 0)
            {
                perror("\nError: ");
                return 0;
            }

            current_joined++;
            printf("Current joined: %d\n", current_joined);
            printf("Waiting room joined: %d\n", waiting_room.joined);
            printf("Client room joined: %d\n", client_room.joined);
        }

        // For each client's room, spawns a thread, and the thread handles the new client's room
        pthread_create(&tid, NULL, &client_handle, (void *)&client_room);
        // pthread_create(&tid, NULL, &client_handle, NULL);
    }
}

void *client_handle(void *arg)
{

    int i;
    client_room_type *client_room_t = (client_room_type *)arg;
    
    int bytes_sent, bytes_received;
    conn_msg_type conn_msg;
    printf("[THREAD} client_room joined: %d\n", client_room_t->joined);

    game_state_type game_state = init_game_state();


    // // Init player
    // for (i = 0; i < client_room.joined; i++)
    // {
    //     game_state.player[i] = init_player(client_room.username[i], client_room.connfd[i]);
    // }

    // for (i = 0; i < client_room.joined; i++)
    // {
    //     printf("Player %d: %s\n", i, game_state.player[i].username);
    // }

    printf("Key: %s\nCrossword: %s\n", game_state.key, game_state.crossword);
    pthread_exit(NULL);
}
