#ifndef CONNECT4_H
#define CONNECT4_H

#define MAX_ROWS 16
#define MAX_COLS 16

// Declare your helper functions here.
int x_in_a_row(int x, int length, int* array, int, int);

void set_up(int* board, int, int, int);

void print_board(int* board, int, int);

void make_move(int* board, int, int, int, int);

#endif