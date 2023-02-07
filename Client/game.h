#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PLAYER_PER_ROOM 3

// Define structure of player
typedef struct player_type_t
{
    char username[50];
    int point;
    // Player's id is specified by host
    int id;
} player_type;

// Define structure of waiting room
typedef struct waiting_room_type_t
{
    player_type player[PLAYER_PER_ROOM];
    int joined;
} waiting_room_type;

// Define structure of sub question
typedef struct sub_question_type_t
{
    char username[50];      // Username of player's turn
    char question[200];
    char answer[3][50];
    char key;
    char guess;
} sub_question_type;

// Define structure of game state
typedef struct game_state_type_t
{
    player_type player[PLAYER_PER_ROOM];

    // Id of current player
    int turn;

    // Current guess char
    char guess_char;

    int wheel[15];

    // Current sector
    int sector;

    // Crossword
    char crossword[50];

    // Host's message
    char game_message[200];
} game_state_type;


// Define function's prototype
game_state_type init_game_state();
waiting_room_type init_waiting_room();
void init_key(char key[]);
void init_crossword(char key[], char crossword[]);
player_type init_player(char username[], int id);
void get_sub_question(sub_question_type *sub_question, char username[]);

void copy_player_type(player_type *dest, player_type src);
void copy_waiting_room_type(waiting_room_type *dest, waiting_room_type src);
void copy_game_state_type(game_state_type *dest, game_state_type src);
void copy_sub_question_type(sub_question_type *dest, sub_question_type src);

int solve_crossword(game_state_type *game_state, char key[], char guess_char);
void roll_wheel(game_state_type *game_state);
int max(int a, int b);


#endif
