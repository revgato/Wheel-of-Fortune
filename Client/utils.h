#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "game.h"
#include "communicate.h"
#include <ctype.h>

int connect_to_server(char *ip, int port);

int disconnect_from_server();

void send_server();

void receive_server();


void print_sub_question(sub_question_type sub_question);

void print_waiting_room(waiting_room_type waiting_room);

void print_game_state(game_state_type game_state);

void handle_game_state(game_state_type *game_state);

char receive_answer();

void handle_sub_question(sub_question_type *sub_question);

void print_notification(char *notification);

int is_valid_guesschar(game_state_type game_state);

#endif