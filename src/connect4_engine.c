/* 
   Devin Merchant
   Fabian Kirberg 

   Place all your Connect4 functions here --- except for main.
   main() needs to go in its own separate .c file.
*/
#include "connect4.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Checks for a Connect 4 win
int x_in_a_row(int x, int length, int* array, int rows, int cols) {
    char token = (x==1) ? '1' : '2';

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            int up_right_counter = 1;
			int down_right_counter = 1;
			int horizontal_counter = 1;
			int vertical_counter = 1;
            char currentIndex = *(array+((i*cols)+j));
 
            //Only check for a win if the current board value is a player's token
			if (currentIndex == token) {

				// Up Right Diagonal Check. Only runs if board has enough room for a win.
				if (i >= length-1) {
					while (up_right_counter < length && currentIndex == token && *(array+((i*cols)+j)-(up_right_counter*cols)+up_right_counter) == token) {
						up_right_counter += 1;
					}
				}

				// Down Right Diagonal and Vertical Check. Only runs if board has enough room for a win.
				if (i <= rows-length) {
					while (down_right_counter < length && currentIndex == token && *(array+((i*cols)+j)+(down_right_counter*cols)+down_right_counter) == token) {
						down_right_counter += 1;
					}
					while (vertical_counter < length && currentIndex == token && *(array+((i*cols)+j)+(vertical_counter*cols)) == token) {
						vertical_counter += 1;
					}
				}

				// Horizontal Check
				while (horizontal_counter < length && currentIndex == token && (((i*cols)+j)+horizontal_counter) < (rows*cols) && ((((i*cols)+j)+horizontal_counter) % cols != 0) && *(array+((i*cols)+j)+horizontal_counter) == token) {
					horizontal_counter += 1;
				}
			}

			//If any of the directional checks reached the winLength, declare a winner and end the game.
			if (up_right_counter == length || down_right_counter == length || horizontal_counter == length || vertical_counter == length) {
				printf("\nCongratulations, Player %d. You win.\n", x);
                return 1;
			}
        }
    }
    return 0;
}

//Sets up board size & sets all values to 0.
void set_up(int* board, int board_height, int board_width, int win_length) {
    for(int i = 0; i < board_height; i++) {
      for(int j = 0; j < board_width; j++) {
        *(board+((i*board_width)+j)) = '0';
         if(j % board_width == 0){
            printf("\n");
         }
        printf("%c ", *(board+((i*board_width)+j)));
      }
   }
   //Prints A, B, C, (etc) based on board size.
   printf("\n");
   for (int i = 65; i <= 65+board_width -1; i++) {
        printf("%c ", i);
    }
    printf("\n");
}

//Print the formatted game board
void print_board(int* board, int board_height, int board_width) {
   for(int i = 0; i < board_height; i++) {
      for(int j = 0; j < board_width; j++) {
         if(j % board_width == 0){
            printf("\n");
         }
        printf("%c ", *(board+((i*board_width)+j)));
      }
   }
   //Prints A, B, C, (etc) based on board size.
   printf("\n");
   for (int i = 65; i <= 65+board_width -1; i++) {
        printf("%c ", i);
    }
}

//Inserts a player's token into the board
void make_move(int* board, int player, int column, int num_rows, int num_cols) {
    char token = (player==1) ? '1' : '2';
 
    for(int i = num_rows-1; i >= 0; i--) {
        if(*(board+((i*num_cols)+(column))) == '0') {
            *(board+((i*num_cols)+(column))) = token;
            break;
        }
    }
}