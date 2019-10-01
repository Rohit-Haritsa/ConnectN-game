//
// Created by Rohit M Haritsa on 2/3/19.
//

#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include "windows.h"
#include "winner.h"


/*
 * switchPlayer -- changes player from player1 to 2 and viceversa
 */
void switchPlayer(int *player) {
    if (*player == PLAYER1) {
        *player = PLAYER2;
    } else {
        *player = PLAYER1;
    }

}

/*
 * If there is space left in the column, returns 1, else zero
 */
int isValidMove(gameBoard *board, int player) {

    if (board->colHeight[board->colPtr] >= 0) {
        return (1);
    } else {
        return (0);
    }
}


/*
 * This main program is overloaded. After initalization of the board, and window, it goes into a main loop until a winner is decided
 * or the board is full.  The logic is straigntforward
 */

int main(int argc, char *argv[]) {

    int rows, columns;
    int length;
    FILE *FP;
    gameBoard board;
    gameWindow win;
    int winner = 0;
    int fullBoard = 0;
    int quit = 0;
    int player = 1;


    rows = atoi(argv[1]);
    columns = atoi(argv[2]);
    length = atoi(argv[3]); // the length of pattern to search
    FP = fopen(argv[4], "w");

    //First, create the board data structure
    board = createBoard(rows, columns, length); //Need to define board;
    // Start Curses
    initscr();
    noecho();
    curs_set(FALSE);

    // Create the windows structure
    win = createGameWindow(rows, columns);
    // Initialize the screen


    updateWin(&win, &board);
    dumpBoard(&board, FP, 0);
    int ch;
    while(!winner && !fullBoard && !quit) {
        ch = wgetch(win.cursorWindow);
        switch (ch) {
            case 'a':
            case 'j':
                wclear(win.messageWindow);
                mvwaddstr(win.messageWindow,0,0,"Moved to the left");
                wrefresh(win.messageWindow);
                updateBoard(&board, player, LEFT, FP);
                updateWin(&win, &board);
                //fprintf(FP, "Dump --> move left\n");
                dumpBoard(&board, FP, 0);
                break;
            case 's':
            case 'k':
                wclear(win.messageWindow);
                mvwaddstr(win.messageWindow,0,0,"Moved to the right");
                wrefresh(win.messageWindow);
                updateBoard(&board,player,RIGHT, FP);
                updateWin(&win,&board);
                //fprintf(FP, "Dump --> move right\n");
                dumpBoard(&board,FP, 0);
                break;
            case ' ':
            case '\n':
                if (isValidMove(&board,player)) {
                    wclear(win.messageWindow);
                    mvwaddstr(win.messageWindow,0,0,"Dropping the piece");
                    updateBoard(&board, player, DROP, FP);
                    updateWin(&win, &board);
                    wrefresh(win.messageWindow);
                    if (((winner = checkWinner(&board, player, FP)) == FALSE) &&
                        ((fullBoard = isFull(&board,player)) == FALSE)) {
                        wclear(win.messageWindow);
                        if(player == PLAYER1) {
                            mvwaddstr(win.messageWindow, 0,0, "Switched to Player2");
                        } else {
                            mvwaddstr(win.messageWindow,0,0,"Switched to Player 1");
                        }
                        wrefresh(win.messageWindow);
                        switchPlayer(&player);
                        updateBoard(&board, player, SWITCH, FP);
                        //fprintf(FP, "Dump --> Dropping the piece\n");
                        dumpBoard(&board, FP, 0);
                        updateWin(&win, &board);
                        //wclear(win.messageWindow);
                        //mvwaddstr(win.messageWindow, 0, 0, "Switched player");
                        //wrefresh(win.messageWindow);
                    }
                } else {
                    //fprintf(FP, "Full column\n");
                    dumpBoard(&board, FP, 0);
                }
                break;
                /*case 'q':
                    wclear(win.messageWindow);
                    mvwaddstr(win.messageWindow,0,0,"You pressed q -- quitting");
                    wrefresh(win.messageWindow);
                    quit=1;
                    break;*/
            default:
                dumpBoard(&board, FP, 0);
                /* wclear(win.messageWindow);
                 mvwaddstr(win.messageWindow,0,0, "You pressed a Wrong key");
                 wrefresh(win.messageWindow);*/
                break;
        }
    }

    endwin();
    dumpBoard(&board, FP, 1);
    dumpBoard(&board, stdout, 1);
    if(fullBoard) {
        fprintf(FP, "Tie Game\n");
        fprintf(stdout, "Tie Game\n");
    } else if (winner){
        fprintf(FP, "Player %d won!\n", player);
        fprintf(stdout, "Player %d won!\n\n", player);
    }
    fclose(FP);
    freeBoard(&board);
    return(0);
}