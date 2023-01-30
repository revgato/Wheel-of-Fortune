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
#include <ctype.h>

// Global variables
client_room_type client_room;

// Handle client tasks
void *client_handle(void *arg);

int specify_turn(int turn, client_room_type client_room);

int is_all_afk(client_room_type client_room);

void summary(game_state_type *game_state);

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
        client_room_type *client_room = init_client_room();
        waiting_room_type waiting_room = init_waiting_room();
        current_joined = 0;

        // Waiting for client to connect (3 clients)
        while (current_joined < PLAYER_PER_ROOM)
        {
            if ((client_room->connfd[current_joined] = accept(listenfd, (struct sockaddr *)client, &sin_size)) == -1)
                perror("\nError: ");
            printf("You got a connection from %s\n", inet_ntoa((*client).sin_addr)); /* Print client's IP */

            // Create new conn_msg variable
            conn_msg_type conn_msg;

            // Receive username from client
            bytes_received = recv(client_room->connfd[current_joined], &conn_msg, sizeof(conn_msg), 0);
            if (bytes_received < 0)
            {
                perror("\nError: ");
                return 0;
            }
            fflush(stdout);
            strcpy(client_room->username[current_joined], conn_msg.data.player.username);
            strcpy(waiting_room.player[current_joined].username, conn_msg.data.player.username);

            // Set active status
            client_room->status[current_joined] = 1;

            client_room->joined++;
            waiting_room.joined++;

            // Send waiting room to client
            copy_waiting_room_type(&conn_msg.data.waiting_room, waiting_room);
            conn_msg = make_conn_msg(WAITING_ROOM, conn_msg.data);
            // printf("Waiting room joined: %d\n", waiting_room.joined);
            // bytes_sent = send(client_room->connfd[current_joined], &conn_msg, sizeof(conn_msg_type), 0);
            send_all(*client_room, conn_msg);
            if (bytes_sent < 0)
            {
                perror("\nError: ");
                return 0;
            }

            current_joined++;
            printf("Current joined: %d\n", current_joined);
            printf("Waiting room joined: %d\n", waiting_room.joined);
            printf("Client room joined: %d\n", client_room->joined);
        }

        // For each client's room, spawns a thread, and the thread handles the new client's room
        pthread_create(&tid, NULL, &client_handle, (void *)client_room);
        // pthread_create(&tid, NULL, &client_handle, NULL);
    }
}

void *client_handle(void *arg)
{

    int i;
    srand(time(0));
    client_room_type client_room = *(client_room_type *)arg;
    free(arg);
    int correct = 1;
    char guess_char;

    int bytes_sent, bytes_received;
    conn_msg_type conn_msg;

    game_state_type game_state = init_game_state();

    // Init player
    for (i = 0; i < client_room.joined; i++)
    {
        game_state.player[i] = init_player(client_room.username[i], client_room.connfd[i]);
    }

    for (i = 0; i < client_room.joined; i++)
    {
        printf("Player %d: %s\n", i, game_state.player[i].username);
    }

    printf("Key: %s\nCrossword: %s\n", game_state.key, game_state.crossword);

    // Loop while crosswords are not solved
    while (strcmp(game_state.crossword, game_state.key) != 0)
    {

        // Clear previous game message
        sprintf(game_state.game_message, "%s", "");

        printf("\n\n\n");
        // [DEBUG] print all client' status
        for (i = 0; i < client_room.joined; i++)
        {
            printf("[DEBUG] Client %d status: %d\n", i, client_room.status[i]);
        }
        // Check AFK
        if (is_all_afk(client_room))
        {
            printf("All players are AFK\n");
            break;
        }
        // Specify current player if previous player's guess is incorrect
        if (correct == 0)
        {
            game_state.turn = specify_turn(game_state.turn, client_room);
            printf("[DEBUG] Current turn: %s\n", game_state.player[game_state.turn].username);
        }

        // Set sector of wheel
        roll_wheel(&game_state);
        printf("[DEBUG] Sector: %d\n", game_state.sector);

        // Handle sector's case
        switch (game_state.sector)
        {
        case -1:

            // TODO: Sub question
            get_sub_question(&game_state.sub_question);

            // Send game state to all clients
            copy_game_state_type(&conn_msg.data.game_state, game_state);
            conn_msg = make_conn_msg(SUB_QUESTION, conn_msg.data);
            send_all(client_room, conn_msg);

            // Receive answer from current player
            bytes_received = recv(client_room.connfd[game_state.turn], &conn_msg, sizeof(conn_msg), 0);
            if (bytes_received < 0)
            {
                perror("\nError: ");
                return 0;
            }

            // Check answer, if correct, add 200 points to current player
            
            if (conn_msg.data.game_state.guess_char == game_state.sub_question.key){
                game_state.player[game_state.turn].point += 200;
                sprintf(game_state.game_message, "Correct answer! [%s] gained 200 points", game_state.player[game_state.turn].username);
                correct = 1;
            }
            else{
                game_state.player[game_state.turn].point -= 100;
                sprintf(game_state.game_message, "Wrong answer! [%s] lost 100 points", game_state.player[game_state.turn].username);
                correct = 0;
            }

            // Send game notification to all clients
            copy_game_state_type(&conn_msg.data.game_state, game_state);
            conn_msg = make_conn_msg(NOTIFICATION, conn_msg.data);
            send_all(client_room, conn_msg);

            break;
        case -2:

            // Minus 150
            game_state.player[game_state.turn].point -= 150;
            sprintf(game_state.game_message, "%s lost 150 points", game_state.player[game_state.turn].username);

            // Send game notification to all clients
            copy_game_state_type(&conn_msg.data.game_state, game_state);
            conn_msg = make_conn_msg(NOTIFICATION, conn_msg.data);
            send_all(client_room, conn_msg);

            // Current player's lost turn
            correct = 0;
            break;
        case -3:

            // Bonus 200
            game_state.player[game_state.turn].point += 200;
            sprintf(game_state.game_message, "%s gained 200 points", game_state.player[game_state.turn].username);

            // Send game notification to all clients
            copy_game_state_type(&conn_msg.data.game_state, game_state);
            conn_msg = make_conn_msg(NOTIFICATION, conn_msg.data);
            send_all(client_room, conn_msg);

            // Current player's lost turn
            correct = 0;
            break;
        default:

            // Send game state to all clients
            copy_game_state_type(&conn_msg.data.game_state, game_state);
            conn_msg = make_conn_msg(GAME_STATE, conn_msg.data);
            send_all(client_room, conn_msg);

            // Receive player's guess
            printf("[DEBUG] Waiting for guess from %d\n", client_room.connfd[game_state.turn]);

            // TRICK to handle bug:
            // Check guess_char is alphabet or not
            guess_char = '0';
            while (!isalpha(guess_char))
            {
                bytes_received = recv(client_room.connfd[game_state.turn], &conn_msg, sizeof(conn_msg), 0);
                if (bytes_received < 0)
                {
                    perror("\nError: ");
                    return 0;
                }
                // TODO: Handle AFK
                guess_char = conn_msg.data.game_state.guess_char;
            }

            printf("[DEBUG] Guess: %c\n", conn_msg.data.game_state.guess_char);

            correct = solve_crossword(&game_state, conn_msg.data.game_state.guess_char);
            printf("[DEBUG] Correct: %d\n", correct);

            // Send result to all clients
            copy_game_state_type(&conn_msg.data.game_state, game_state);
            conn_msg = make_conn_msg(NOTIFICATION, conn_msg.data);
            send_all(client_room, conn_msg);
            break;
        }

        // sector of wheel
    }
    summary(&game_state);
    // Send game summary to all clients
    copy_game_state_type(&conn_msg.data.game_state, game_state);
    conn_msg = make_conn_msg(END_GAME, conn_msg.data);
    send_all(client_room, conn_msg);

    pthread_exit(NULL);
}

int specify_turn(int turn, client_room_type client_room)
{

    // Find next active player
    int current_turn = (turn + 1) % client_room.joined;

    while (client_room.status[current_turn] != 1 && current_turn != turn)
    {
        // printf("[DEBUG] old_turn: %d, specify_turn: %d, connfd: %d\n", turn, current_turn, client_room.connfd[current_turn]);
        current_turn = (current_turn + 1) % client_room.joined;
    }

    return current_turn;
}

int is_all_afk(client_room_type client_room)
{

    // Check if all players are afk
    int i;
    for (i = 0; i < client_room.joined; i++)
    {
        if (client_room.status[i] == 1)
        {
            return 0;
        }
    }
    return 1;
}

void summary(game_state_type *game_state){
    // Write summary to game_state->game_message
    int i;
    char temp[100];
    int max_point = 0;
    int winner = 0;
    sprintf(game_state->game_message, "Summary:\n");
    for (i = 0; i < PLAYER_PER_ROOM; i++){
        if (game_state->player[i].point > max_point){
            max_point = game_state->player[i].point;
            winner = i;
        }
        sprintf(temp, "%s: %d points\n", game_state->player[i].username, game_state->player[i].point);
        strcat(game_state->game_message, temp);
    }
    sprintf(temp, "Winner: %s\n", game_state->player[i].username);
    strcat(game_state->game_message, temp);
}
