//
// Created by Rohit M Haritsa on 2/3/19.
//


#ifndef CONNECTN_BOARD_H
#define CONNECTN_BOARD_H


#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int **cells;
    int *colHeight; // used to keep tabs on how much the column is filled. If this is = columns, then it's not a valid move
    int *cursorLoc; // The top row -- which has the cursor -- an 1D array of width columns
    int rows;
    int columns;
    int patternLength; // Number of bits to check for.
    int colPtr; // This is the pointer that tells where the player is. This means no searching!

} gameBoard;


#define PLAYER1 1
#define PLAYER2 2

#define LEFT 1
#define RIGHT 2
#define DROP 3
#define SWITCH 4


#define PLAYER1SYMBOL "X"
#define PLAYER2SYMBOL "O"
#define EMPTYSYMBOL "*"


// Function prototypes

gameBoard createBoard(int x, int y, int patternLength);
void updateBoard(gameBoard *board, int player, int command, FILE *FP);
char mapBoard(int num);
void dumpBoard(gameBoard *board, FILE *fp, int gameOver);
void freeBoard(gameBoard *board);

#endif //CONNECTN_BOARD_H
