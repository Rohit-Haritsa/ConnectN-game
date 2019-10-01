/*
 * Midterm1 - ECS36B
 */

#ifndef NCONNECTN_WINDOWS_H
#define NCONNECTN_WINDOWS_H

#include <ncurses.h>
#include "board.h"

typedef struct {
    WINDOW *cursorWindow;
    WINDOW *boardWindow;
    WINDOW *messageWindow;
} gameWindow;

#endif //NCONNECTN_WINDOWS_H

gameWindow createGameWindow(int rows, int columns);
void updateWin(gameWindow *win, gameBoard *board);