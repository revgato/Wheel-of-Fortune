#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char question[200];
    char answer[3][50];
    char key;
} sub_question_type;

// Define structure of game state
typedef struct game_state_type_t
{
    player_type player[PLAYER_PER_ROOM];

    // Id of current player
    int turn;

    // Current guess char
    char guess_char;

    int sectors[15];

    // Current sector
    int sector;

    // Crossword and key
    char key[50];
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
void get_sub_question(sub_question_type *sub_question);

// Function's body
player_type init_player(char username[], int id)
{
    player_type player;
    strcpy(player.username, username);
    player.point = 0;
    player.id = id;
    return player;
}

waiting_room_type init_waiting_room()
{
    waiting_room_type waiting_room;
    waiting_room.joined = 0;
    return waiting_room;
}

game_state_type init_game_state()
{
    game_state_type game_state;


    // Sector description:
    // -1: Sub question (150 point)
    // -2: Minus 150 point
    // -3: Bonus 200 point
    // Other: points

    // Init sectors
    game_state.sectors[0] = 100;
    game_state.sectors[1] = 200;
    game_state.sectors[2] = 400;
    game_state.sectors[3] = 200;
    game_state.sectors[4] = -1;
    game_state.sectors[5] = 100;
    game_state.sectors[6] = 200;
    game_state.sectors[7] = 300;
    game_state.sectors[8] = 100;
    game_state.sectors[9] = -2;
    game_state.sectors[10] = 200;
    game_state.sectors[11] = 300;
    game_state.sectors[12] = 100;
    game_state.sectors[13] = -3;
    game_state.sectors[14] = 200;

    // Init key
    init_key(game_state.key);

    // Init crossword by binding key
    init_crossword(game_state.key, game_state.crossword);

    // Init turn, start from 1
    game_state.turn = 1;

}


// Init key by random pick 1 line from key.txt
void init_key(char key[])
{
    FILE *f = fopen("key.txt", "r");
    if (f == NULL)
    {
        printf("Error opening key.txt file!\n");
        exit(1);
    }

    // Get number of line in file
    int num_line = 0;
    char c;
    for (c = getc(f); c != EOF; c = getc(f))
        if (c == '\n')
            num_line = num_line + 1;

    // Random pick 1 line
    int random_line = rand() % num_line;
    int i = 0;
    while (i < random_line)
    {
        if (c == '\n')
            i = i + 1;
        c = getc(f);
    }

    // Get key
    fscanf(f, "%s", key);
    fclose(f);

    return;
}

// Init crossword by binding key
void init_crossword(char key[], char crossword[])
{
    int i;
    for (i = 0; i < strlen(key); i++)
    {
        if (key[i] == ' ')
            crossword[i] = ' ';
        else
            crossword[i] = '*';
    }
}

// Get sub question by random pick 1 question from sub_question.txt
void get_sub_question(sub_question_type *sub_question)
{
    FILE *f = fopen("sub_question.txt", "r");
    if (f == NULL)
    {
        printf("Error opening sub_question.txt file!\n");
        exit(1);
    }

    // Get number of line in file
    int num_line = 0;
    char c;
    for (c = getc(f); c != EOF; c = getc(f))
        if (c == '\n')
            num_line = num_line + 1;

    // Random pick 1 line
    int random_line = rand() % num_line;
    // Scale to divide by 4
    random_line = random_line - random_line % 5;
    int i = 0;
    while (i < random_line)
    {
        if (c == '\n')
            i = i + 1;
        c = getc(f);
    }

    // Get sub question
    fscanf(f, "%[^\n]%*c", sub_question->question);
    fscanf(f, "%[^\n]%*c", sub_question->answer[0]);
    fscanf(f, "%[^\n]%*c", sub_question->answer[1]);
    fscanf(f, "%[^\n]%*c", sub_question->answer[2]);
    fscanf(f, "%c%*c", &sub_question->key);
    fclose(f);
}


#endif