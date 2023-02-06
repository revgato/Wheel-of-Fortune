#include "game.h"


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

game_state_type init_game_state(char key[])
{
    game_state_type game_state;

    // Sector description:
    // -1: Sub question (150 point)
    // -2: Minus 150 point
    // -3: Bonus 200 point
    // Other: points

    // Init wheel
    game_state.wheel[0] = 100;
    game_state.wheel[1] = 200;
    game_state.wheel[2] = 400;
    game_state.wheel[3] = 200;
    game_state.wheel[4] = -1;
    game_state.wheel[5] = 100;
    game_state.wheel[6] = 200;
    game_state.wheel[7] = 300;
    game_state.wheel[8] = 100;
    game_state.wheel[9] = -2;
    game_state.wheel[10] = 200;
    game_state.wheel[11] = 300;
    game_state.wheel[12] = 100;
    game_state.wheel[13] = -3;
    game_state.wheel[14] = 200;

    // game_state.wheel[0] = -1;
    // game_state.wheel[1] = 200;
    // game_state.wheel[2] = -1;
    // game_state.wheel[3] = 200;
    // game_state.wheel[4] = -2;
    // game_state.wheel[5] = 100;
    // game_state.wheel[6] = -2;
    // game_state.wheel[7] = 300;
    // game_state.wheel[8] = -2;
    // game_state.wheel[9] = -2;
    // game_state.wheel[10] = 200;
    // game_state.wheel[11] = -1;
    // game_state.wheel[12] = 100;
    // game_state.wheel[13] = -3;
    // game_state.wheel[14] = 200;


    // Init crossword by binding key
    init_crossword(key, game_state.crossword);

    // Init turn, start from 0
    game_state.turn = 0;

    return game_state;

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

    // Move f pointer to head of file
    rewind(f);

    // Move pointer to the key
    while (i < random_line)
    {
        c = getc(f);
        if (c == '\n')
            i = i + 1;
    }

    // Get key
    fscanf(f, "%[^\n]", key);
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
void get_sub_question(sub_question_type *sub_question, char username[])
{
    sub_question->guess = '0';
    strcpy(sub_question->username, username);
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

    // Move f pointer to head of file
    rewind(f);

    while (i < random_line)
    {
        c = getc(f);
        if (c == '\n')
            i = i + 1;
    }

    // Get sub question
    fscanf(f, "%[^\n]%*c", sub_question->question);
    fscanf(f, "%[^\n]%*c", sub_question->answer[0]);
    fscanf(f, "%[^\n]%*c", sub_question->answer[1]);
    fscanf(f, "%[^\n]%*c", sub_question->answer[2]);
    fscanf(f, "%c%*c", &sub_question->key);
    fclose(f);
}

void copy_player_type(player_type *dest, player_type src)
{
    strcpy(dest->username, src.username);
    dest->point = src.point;
    dest->id = src.id;
}

void copy_waiting_room_type(waiting_room_type *dest, waiting_room_type src)
{
    for (int i = 0; i < PLAYER_PER_ROOM; i++)
    {
        copy_player_type(&dest->player[i], src.player[i]);
    }
    dest->joined = src.joined;
}

void copy_game_state_type(game_state_type *dest, game_state_type src)
{
    // Copy player
    for (int i = 0; i < PLAYER_PER_ROOM; i++)
    {
        copy_player_type(&dest->player[i], src.player[i]);
    }

    // Copy wheel
    dest->turn = src.turn;
    dest->guess_char = src.guess_char;
    for (int i = 0; i < 15; i++)
    {
        dest->wheel[i] = src.wheel[i];
    }
    dest->sector = src.sector;

    // Copy crossword
    strcpy(dest->crossword, src.crossword);


    strcpy(dest->game_message, src.game_message);
}

void copy_sub_question_type(sub_question_type *dest, sub_question_type src){
    strcpy(dest->question, src.question);
    strcpy(dest->answer[0], src.answer[0]);
    strcpy(dest->answer[1], src.answer[1]);
    strcpy(dest->answer[2], src.answer[2]);
    dest->key = src.key;
    dest->guess = src.guess;
    strcpy(dest->username, src.username);
}

int solve_crossword(game_state_type *game_state, char key[], char guess_char){

    // Check if guess_char is in key
    int i;
    int is_in_key = 0;

    for (i = 0; i < strlen(key); i++)
    {
        if (key[i] == guess_char)
        {
            is_in_key++;
            game_state->crossword[i] = guess_char;
        }
    }

    // If guess_char is in key, add point to this player
    // Show message
    if (is_in_key > 0){
        game_state->player[game_state->turn].point += is_in_key * game_state->sector;
        sprintf(game_state->game_message, "There are %d %c in the key. [%s] get %d points\n",
            is_in_key, guess_char, game_state->player[game_state->turn].username , is_in_key * game_state->sector);
    }else{
        sprintf(game_state->game_message, "There is no %c in the key.\n", guess_char);
    }

    return is_in_key;
}

void roll_wheel(game_state_type *game_state){
    // Random pick 1 number from wheel
    int random_number = rand() % 15;
    game_state->sector = game_state->wheel[random_number];
}

int max(int a, int b){
    return a > b? a : b;
}

