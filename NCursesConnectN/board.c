//
// Created by Rohit M Haritsa on 2/3/19.
//

#include "board.h"
#include <ncurses.h>
#include <unistd.h>
#include <string.h>

/*
 * Freeing the Game board
 */

void freeBoard(gameBoard *board) {

    int *row;
    int i;
    for (i = 0; i < board->rows; i++) {
        row = board->cells[i];
        free(row);
    }
    free(board->cells);
    free(board->colHeight);
    free(board->cursorLoc);
}

/*
 * Creating the gameBoard -- the structure is overloaded with all information for board management
 * Current column pointer to show which column the game piece is at
 * The height to show if the board is full or empty (starts from the bottom -- set to # rows)
 */
gameBoard createBoard(int numRows, int numCols, int patternLength) {

    int i, j;

    gameBoard board;
    //printf("Creating a board of rows %d and columns %d\n", numRows, numCols);
    board.colHeight = (int *) malloc(numCols * sizeof(int));
    board.cursorLoc = (int *) malloc(numCols * sizeof(int));
    board.colPtr = 0;

    board.cells = (int **) malloc(numRows * sizeof(int *));
    for (i = 0; i < numRows; i++) {
        board.cells[i] = (int *) malloc(numCols * sizeof(int));
    }
// Initialize the board
    for (i = 0; i < numRows; i++) {
        for (j = 0; j < numCols; j++) {
            board.cells[i][j] = 0;
            board.colHeight[j] = numRows-1;// numCols means pointer is at nth row -- empty.  Keep decreasing
            if (j == 0) {
                board.cursorLoc[0] = PLAYER1;
            } else {
                board.cursorLoc[j] = 0;
            }

        }
    }
    board.patternLength = patternLength;
    board.columns = numCols;
    board.rows = numRows;
    return (board);
}

/*
 * Updates the board to show the piece moving left, right or being dropped.
 * The main program,and stores all information
 */
void updateBoard(gameBoard *board, int player, int command, FILE *FP) {
    int i;
    if (command == LEFT) {
        for (i = 0; i < board->columns; i++) {
            if (i == 0) {
                if (board->cursorLoc[i] == player) {
                    // Wrap around to the left
                    board->cursorLoc[i] = 0;
                    board->cursorLoc[(board->columns-1)] = player;
                    board->colPtr = (board->columns-1);
                    return;
                }
            } else {
                if (board->cursorLoc[i] == player) {
                    // shift left
                    board->cursorLoc[i - 1] = player;
                    board->cursorLoc[i] = 0;
                    board->colPtr = i-1;
                    //fprintf(FP, "Moved to the left, column pointer is now %d\n", board->colPtr);
                    return;
                }
            }
        }
    } else if (command == RIGHT) {
        // Right shift
        for (i = 0; i < board->columns; i++) {
            if (i == (board->columns - 1)) { // last column in the array
                if (board->cursorLoc[i] == player) {
                    // Wrap around to the left
                    board->cursorLoc[0] = player;
                    board->cursorLoc[(board->columns - 1)] = 0;
                    board->colPtr = 0;
                    //fprintf(FP, "Moved to the RIGHT, column pointer is now %d\n", board->colPtr);
                    return;
                }
            } else {
                if (board->cursorLoc[i] == player) {
                    // shift left
                    board->cursorLoc[i + 1] = player;
                    board->cursorLoc[i] = 0;
                    board->colPtr = i + 1;
                    //fprintf(FP, "Moved to the RIGHT, column pointer is now %d\n", board->colPtr);
                    return;
                }
            }
        }
    } else if (command == SWITCH) {
        board->cursorLoc[board->colPtr] = player;
    } else {
        // Have to drop
        //fprintf(FP, "Dropped player %d to cell[%d][%d]\n", player, board->colPtr, board->colHeight[board->colPtr]);
        board->cells[board->colHeight[board->colPtr]][board->colPtr] = player;
        board->colHeight[board->colPtr]--;
    }
}


char mapBoard(int num) {
    if (num == 0) {
        return ('*');
    } else if (num == 1) {
        return ('X');
    } else {
        return ('O');
    }
}


void dumpBoard(gameBoard *board, FILE *fp, int gameOver) {
    int i, j;
    for (i = 0; i < board->columns; i++) {
        if (board->cursorLoc[i] == 0) {
            fprintf(fp, "%c", 32);
        } else {
            fprintf(fp, "%c", mapBoard(board->cursorLoc[i]));
        }
    }
    fprintf(fp, "\n");

    for (i = 0; i < board->rows; i++) {
        for (j = 0; j < board->columns; j++) {
            fprintf(fp, "%c", mapBoard(board->cells[i][j]));
        }
        fprintf(fp, "\n");
    }
    if (!gameOver) {
        fprintf(fp, "\n\n");
    }
}

