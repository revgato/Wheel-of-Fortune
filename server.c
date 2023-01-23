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

// Handle client tasks
void *client_handle(void *);

int main()
{
    int listenfd, *connfd;
    struct sockaddr_in server, *client; // Server's address information
    int sin_size;
    pthread_t tid;

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
        // Waiting for client to connect (3 clients)
        while (client_room.slot != 0)
        {
            if ((client_room.connfd[client_room.slot - 1] = accept(listenfd, (struct sockaddr *)client, &sin_size)) == -1)
                perror("\nError: ");
            printf("You got a connection from %s\n", inet_ntoa((*client).sin_addr)); /* Print client's IP */
            // TODO: Receive username from client

            // TODO: Send waiting room to client

            client_room.slot--;
        }

        // For each client's room, spawns a thread, and the thread handles the new client's room
        pthread_create(&tid, NULL, &client_handle, &client_room);
    }
}

void *client_handle(void *arg)
{
    client_room_type client_room = *(client_room_type *)arg;
    int bytes_sent, bytes_received;
    game_state_type game_state = init_game_state();


    // Init player
    for (int i = 0; i < PLAYER_PER_ROOM; i++)
    {
        game_state.player[i] = init_player(client_room.username[i], client_room.connfd[i]);
    }

    // 21/1/2023: Init player in game state
}
