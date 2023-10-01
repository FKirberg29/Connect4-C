/* 
   Devin Merchant
   Fabian Kirberg

   Place your Connect4's main() function here.
   Anything that you want unit tested must go in a separate file.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <regex.h>
#include "connect4.h"


#define MAX_ROWS 16
#define MAX_COLS 16
#define INPUT_MAX 2

int main(int argc, char *argv[]) {

    int board_height, board_width, win_length;
    int* board = malloc((MAX_ROWS * MAX_COLS) * sizeof(int));
    bool winner = false;
    int player = 1;
    char input[INPUT_MAX];
    char chr;

    //Compile regex used for input validation
    regex_t regex;
    regcomp(&regex, "^[0-9]*[x][0-9]*$", 0);

    //If no arguments, standard game.
    if (argc < 2) {
        printf("Connect 4. 6x7 Board. Win length 4.");
        board_height = 6;
        board_width = 7;
        win_length = 4;
        set_up(board, board_height, board_width, win_length);
    }

    //If 1 argument, use as board size
    if (argc == 2) {
        //Check for proper formatting
        char* input = argv[1];
        int match = regcomp(&regex, input, 0);
        if (match == 0) {
            sscanf(argv[1], "%dx%d", &board_height, &board_width);
            win_length = 4;
            printf("Connect 4. %dx%d board. Win length %d.", board_height, board_width, win_length);
            set_up(board, board_height, board_width, win_length);
        } else {
            printf("Input format is not valid, please try again.\n");
            exit(1);
        }
    }

    //If 2 or more arguments, use first 2 as board size and win length
    if (argc >= 3) {
        //Check for proper formatting
        char* input = argv[1];
        int match = regcomp(&regex, input, 0);
        if (match == 0) {
            sscanf(argv[1], "%dx%d", &board_height, &board_width);
            sscanf(argv[2], "%d", &win_length);
            printf("Connect 4. %dx%d board. Win length %d.", board_height, board_width, win_length);
            set_up(board, board_height, board_width, win_length);
        } else {
            printf("Input format is not valid, please try again.\n");
            exit(1);
        }
    }

    //Loop until winner
    while (winner == false) {        
        printf("\nPlayer %d, please enter a column: ", player);

        //Get user input and account for trailing newline character.
        fgets(input, INPUT_MAX, stdin);
        sscanf(input, "%c", &chr);
        if (chr == '\n') {
            fgets(input, INPUT_MAX+1, stdin);
            sscanf(input, "%c", &chr);
        }
        chr = toupper(chr);

        //If user inputs "q" or "Q", quit.
        if (chr == 'Q') {
            printf("Goodbye.");
            break;
        }

        //If character chosen is invalid
        if ((int)chr <= 64 || (int)chr > 64+board_width) {
            printf("\nInvalid input, please try again.");
            continue;
        }

        //Character must be in the bounds of the game
        if (chr > 64 && chr <= 64+board_width) {
            if (*(board+(chr-'A')) != '0') {
                printf("\nThis column is full, please select another.");
                continue;
            }
            //If column is not full, make move and check for win
            make_move(board, player, chr-'A', board_height, board_width);
            print_board(board, board_height, board_width);
            if(x_in_a_row(player, win_length, board, board_height, board_width) == 1) {
                free(board);
                exit(1);
            }
        } else {
            printf("Invalid input, please try again.");
            continue;
        }

        // If a player successfully places their token, swap players and request new input.
        player = (player == 1) ? 2 : 1;
    }
    return 0;
}