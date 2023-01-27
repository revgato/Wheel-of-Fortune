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
#include <ctype.h>

conn_data_type conn_data;
conn_msg_type conn_msg;
char username[50];
char guess_char;
int client_sock;

void send_server(int connfd, conn_msg_type conn_msg)
{
    int bytes_sent;
    bytes_sent = send(connfd, &conn_msg, sizeof(conn_msg), 0);
    if (bytes_sent < 0)
    {
        printf("Error: Cannot send message to server!\n");
        exit(1);
    }
}

void print_title()
{
    printf("Wheel of Fortune\n");
    printf("====================================\n\n");
}

void print_sub_question(sub_question_type sub_question)
{
    printf("Sub question:\n");
    printf("%s\n", sub_question.question);
    printf("A. %s\n", sub_question.answer[0]);
    printf("B. %s\n", sub_question.answer[1]);
    printf("C. %s\n", sub_question.answer[2]);
}

void print_waiting_room(waiting_room_type waiting_room)
{
    // Clear screen
    printf("\033[2J");

    // Print title
    print_title();

    // Print waiting room
    printf("Waiting room:\n");
    printf("Waiting room joined: %d\n", waiting_room.joined);
    for (int i = 0; i < waiting_room.joined; i++)
    {
        printf("Player %d: %s\n", i + 1, waiting_room.player[i].username);
    }
    printf("\n");
}

void print_game_state(game_state_type game_state)
{

    // Clear screen
    printf("\033[2J");

    // Print title
    print_title();

    // Print game state
    printf("====================================\n\n");
    printf("Game state:\n\n");

    // Print player
    for (int i = 0; i < PLAYER_PER_ROOM; i++)
    {
        printf("Player %d: %s\n", i + 1, game_state.player[i].username);
        printf("Point: %d\n\n", game_state.player[i].point);
    }

    // Print server's message
    printf("Server's message: \n%s\n", game_state.game_message);

    // Print sector
    printf("Current sector: %d\n", game_state.sector);

    // Print crossword
    printf("Crossword:\n");
    printf("%s\n", game_state.crossword);

    // Print current player
    printf("[DEBUG] Current turn: %d\n", game_state.turn);
    printf("Current player: %s\n", game_state.player[game_state.turn].username);

    return;
}

void handle_game_state(game_state_type *game_state)
{
    int i;
    int bytes_sent;

    print_game_state(*game_state);

    // If it's my turn
    if (strcmp(game_state->player[game_state->turn].username, username) == 0)
    {
        printf("Please enter your guess: ");

        // Check guess_char is alphabet
        game_state->guess_char = '0';
        while (!isalpha(game_state->guess_char))
        {
            fflush(stdin);
            game_state->guess_char = getchar();
        }

        game_state->guess_char = toupper(game_state->guess_char);

        // Send guess char to server
        copy_game_state_type(&conn_msg.data.game_state, *game_state);
        conn_msg = make_conn_msg(GUESS_CHAR, conn_msg.data);
        send_server(client_sock, conn_msg);
    }
}

int main()
{
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
    scanf("%s%*c", username);
    player_type player = init_player(username, -1);

    printf("Connecting to server...\n");
    // Init communicate message
    copy_player_type(&conn_data.player, player);
    conn_msg = make_conn_msg(JOIN, conn_data);

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
        printf("Waiting for server's response...\n");
        bytes_received = recv(client_sock, &conn_msg, sizeof(conn_msg), 0);
        if (bytes_received <= 0)
        {
            perror("\nError: ");
            close(client_sock);
            return 0;
        }
        fflush(stdout);

        // Handle message from server
        switch (conn_msg.type)
        {
        case JOIN:
            // TODO: Handle join message
            break;
        case WAITING_ROOM:
            // TODO: Handle waiting room message
            print_waiting_room(conn_msg.data.waiting_room);
            break;
        case GAME_STATE:
            handle_game_state(&conn_msg.data.game_state);
            printf("Press any key to continue...");
            getchar();
            // TODO: Handle game state message
            break;
        case SUB_QUESTION:
            print_game_state(conn_msg.data.game_state);
            print_sub_question(conn_msg.data.game_state.sub_question);

            printf("Press any key to continue...");
            getchar();
            break;

        case NOTIFICATION:
            print_game_state(conn_msg.data.game_state);

            printf("Press any key to continue...");
            getchar();
            break;
        }
    }

    // Step 5: Close socket
    close(client_sock);
    return 0;
}
