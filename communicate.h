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

// Define client's room
typedef struct client_room_type_t
{
    int connfd[PLAYER_PER_ROOM];

    // status of client
    // 0: not ready, 1: ready, -1: AFK
    int status[PLAYER_PER_ROOM];
    int slot;
} client_room_type;

// Define function's prototype
conn_msg_type make_conn_msg(conn_msg_type_type type, conn_data_type data);
void copy_player_type(player_type *dest, player_type src);
void copy_waiting_room_type(waiting_room_type *dest, waiting_room_type src);
void copy_game_state_type(game_state_type *dest, game_state_type src);
client_room_type init_client_room();

// Define function's body

void copy_player_type(player_type *dest, player_type src){
    strcpy(dest->username, src.username);
    dest->point = src.point;
    dest->id = src.id;
}

void copy_waiting_room_type(waiting_room_type *dest, waiting_room_type src){
    for(int i = 0; i < PLAYER_PER_ROOM; i++){
        copy_player_type(&dest->player[i], src.player[i]);
    }
    dest->slot = src.slot;
}

void copy_game_state_type(game_state_type *dest, game_state_type src){
    for(int i = 0; i < PLAYER_PER_ROOM; i++){
        copy_player_type(&dest->player[i], src.player[i]);
    }
    dest->turn = src.turn;
    dest->guess_char = src.guess_char;
    for(int i = 0; i < 15; i++){
        dest->sectors[i] = src.sectors[i];
    }
    dest->sector = src.sector;
    strcpy(dest->key, src.key);
    strcpy(dest->crossword, src.crossword);
    strcpy(dest->game_message, src.game_message);
}

conn_msg_type make_conn_msg(conn_msg_type_type type, conn_data_type data){
    conn_msg_type conn_msg;
    conn_msg.type = type;
    switch(type){
        case JOIN:
            copy_player_type(&conn_msg.data.player, data.player);
            break;
        case WAITING_ROOM:
            copy_waiting_room_type(&conn_msg.data.waiting_room, data.waiting_room);
            break;
        // case START:
        //     conn_msg.data.game = data.game;
        //     break;
        // case POINT:
        //     conn_msg.data.player = data.player;
        //     break;
        case GAME_STATE:
            copy_game_state_type(&conn_msg.data.game, data.game);
            break;
        case GUESS_CHAR:
            copy_game_state_type(&conn_msg.data.game, data.game);
            break;
    }
}

client_room_type init_client_room(){
    client_room_type client_room;
    for(int i = 0; i < PLAYER_PER_ROOM; i++){
        client_room.connfd[i] = -1;
        client_room.status[i] = 0;
    }
    client_room.slot = PLAYER_PER_ROOM;
    return client_room;
}
#endif
