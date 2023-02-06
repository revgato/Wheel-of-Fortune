#ifndef COMMUNICATE_H
#define COMMUNICATE_H

#include <stdlib.h>
#include "game.h"

#define BUFF_SIZE 1024
#define BACKLOG 30 // Maximum number of client can connect to server
#define WAIT_TIME 15
#define SLEEP_TIME 1
// Define communicate message
typedef enum conn_msg_type_type_t
{
    JOIN,
    REFUSE,
    WAITING_ROOM,
    GAME_STATE,
    GUESS_CHAR,
    NOTIFICATION,
    SUB_QUESTION,
    END_GAME
} conn_msg_type_type;

// Define data of communicate message
typedef union conn_data_type_t
{
    game_state_type game_state;
    player_type player;
    waiting_room_type waiting_room;
    char notification[300];
    sub_question_type sub_question;
} conn_data_type;

// Define communicate message
typedef struct conn_msg_type_t
{
    conn_msg_type_type type;
    conn_data_type data;
} conn_msg_type;

// Define client's room
typedef struct client_room_type_t
{
    int connfd[PLAYER_PER_ROOM];
    char username[PLAYER_PER_ROOM][50];
    // status of client
    // 0: not ready, 1: ready, -1: AFK
    int status[PLAYER_PER_ROOM];
    int joined;
} client_room_type;

// Define function's prototype
conn_msg_type make_conn_msg(conn_msg_type_type type, conn_data_type data);

client_room_type *init_client_room();
void send_all(client_room_type client_room, conn_msg_type conn_msg);
int check_afk(int bytes_communicate, client_room_type *client_room, int turn);



#endif
