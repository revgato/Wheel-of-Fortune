#ifndef COMMUNICATE_H
#define COMMUNICATE_H

#include <stdlib.h>
#include "game.h"

#define SERVER_PORT 5500
#define BUFF_SIZE 1024
#define BACKLOG 30
#define SERVER_ADDR "127.0.0.1"

// Define communicate message
typedef enum conn_msg_type_type_t
{
    JOIN,
    WAITING_ROOM,
    // START,
    // POINT,
    GAME_STATE,
    GUESS_CHAR
} conn_msg_type_type;

// Define data of communicate message
typedef union conn_data_type_t{
    game_state_type game;
    player_type player;
    waiting_room_type waiting_room;    
} conn_data_type;

// Define communicate message
typedef struct conn_msg_type_t
{
    conn_msg_type_type type;
    conn_data_type data;
} conn_msg_type;

conn_msg_type make_conn_msg(conn_msg_type_type type, conn_data_type data){
    conn_msg_type conn_msg;
    conn_msg.type = type;
    switch(type){
        case JOIN:
            conn_msg.data.player = data.player;
            break;
        case WAITING_ROOM:
            conn_msg.data.waiting_room = data.waiting_room;
            break;
        // case START:
        //     conn_msg.data.game = data.game;
        //     break;
        // case POINT:
        //     conn_msg.data.player = data.player;
        //     break;
        case GAME_STATE:
            conn_msg.data.game = data.game;
            break;
        case GUESS_CHAR:
            conn_msg.data.game = data.game;
            break;
    }
}
#endif
