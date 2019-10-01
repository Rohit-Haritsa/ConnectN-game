//
// Created by Rohit M Haritsa on 2/3/19.
//


#include "winner.h"
#include "board.h"
#include <ncurses.h>

/*
 * Checks to see if the board is full
 */
int isFull(gameBoard *board, int playerType) {
    // Just check to see if all the colPtrs are zero.

    int i;
    for (i = 0; i < board->columns; i++) {
        if (board->colHeight[i] >= 0) {
            return(0);
        }
    }
    return(1);
}

/*
 * Check to see if the diagonal (right to left) has the required pattern
 *
 */

int isDiagonalWinnerRightToLeft(gameBoard *board, int playerType) {
    int i,j,k;
    k = 0;
    int count = 0;

    for(j=(board->columns-1); j>=0; j--) {
        count = 0;
        for (i=0; (i < board->rows && (j-i) >=0); i++) {
            if(board->cells[i][j-i] == playerType) {
                count++;
            } else {
                count = 0;
            }
            if (count >= board->patternLength) {
                return(1);
            }

        }
    }

    for (i=1; i < board->rows; i++) {
        count = 0;
        k = i;
        for (j = (board->columns - 1); (j >= 0 && k < board->rows); j--) {
            if (board->cells[k][j] == playerType) {
                count++;
            } else {
                count = 0;
            }
            k++;
            if (count >= board->patternLength) {
                return (1);
            }
        }
    }
    return(0);

}

/*
 * Checks to see the L->R diagonal has the required patternLength
 */

int isDiagonalWinnerLeftToRight(gameBoard *board, int playerType)
{
    int i,j;
    int min_dimension;
    int count = 0;
    if (board->rows > board->columns) {
        min_dimension = board->columns;
    } else {
        min_dimension = board->rows;
    }
    for (j = 0; j < board->columns; j++) {
        count=0;
        for (i = 0; (i < min_dimension && (i+j) < board->columns); i++) {
            if(board->cells[i][i+j] == playerType) {
                count++;
            } else {
                count = 0;
            }
            if (count >= board->patternLength) {
                return(1);
            }
        }
    }
    // Can skip the first cell -- so, start from j=1. Some optimization
    for (j = 1; j < board->rows; j++) {
        count=0;
        for (i = 0; (i < min_dimension && (i+j) < board->rows); i++) {
            if(board->cells[i+j][i] == playerType) {
                count++;
            } else {
                count = 0;
            }
            if (count >= board->patternLength) {
                return(1);
            }
        }
    }
    return(0);

}


int is_horizontal_winner(gameBoard *board, int playerType) {
    int i, j;
    int count = 0;
    for (i = 0; i < board->rows; i++) {
        count = 0;
        for (j = 0; j < board->columns; j++) {
            if (board->cells[i][j] == playerType) {
                count++;
            } else {
                count = 0;
            }
            if (count >= board->patternLength) {
                return (1);
            }
        }
    }
    return (0);
}

int is_vertical_winner(gameBoard *board, int playerType){
    int i,j;
    int count = 0;
    for(i=0;i<board->columns;i++){
        count = 0;
        for(j=0;j<board->rows;j++){
            if(board->cells[j][i]==playerType){
                count++;
            }
            else{
                count=0;
            }
        }
        if(count >= board->patternLength) {
            return 1;
        }
    }
    return(0);
}


int checkWinner(gameBoard *board, int playerType, FILE *fp) {

    //def_prog_mode();
    //endwin();
    //fprintf(stdout, "Checking for length %d of player %d\n", board->patternLength, playerType);
    if (is_vertical_winner(board, playerType)) {
        //printf("Found a vertical winner of type %d of length %d\n", playerType, board->patternLength);
        return(1);
    } else if (is_horizontal_winner(board, playerType)) {
        // printf("Found a horizontal winner of type %d of length %d\n", playerType, board->patternLength);
        return(1);
    } else if(isDiagonalWinnerLeftToRight(board, playerType)) {
        //printf("Found a diagonal pattern\n");
        return (1);
    }else if(isDiagonalWinnerRightToLeft(board, playerType)) {
        return(1);
    } else {
        // reset_prog_mode();
        // refresh();
        return(0);
    }

}
