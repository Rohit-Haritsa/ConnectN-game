/*
 * Midterm1 - ECS36B
 */

#include "windows.h"
#include "board.h"

gameWindow createGameWindow(int rows, int columns) {
    gameWindow win;

    // Now create three windows, one on top of the other
    win.cursorWindow = newwin(1,columns,0,0);
    refresh();
    win.boardWindow = newwin(rows,columns,1 ,0);
    refresh();
    win.messageWindow = newwin(1,50,(rows+2), 0);
    refresh();

    return(win);

}


void updateWin(gameWindow *win, gameBoard *board) {
    int i, j;
    // First the cursor board
    wclear(win->cursorWindow);
    for (i = 0; i < board->columns; i++) {
        switch(board->cursorLoc[i]) {
            case 0:
                mvwaddch(win->cursorWindow, 0,i,32);
                break;
            case 1:
                mvwaddch(win->cursorWindow,0,i,88);
                break;
            case 2:
                mvwaddch(win->cursorWindow,0,i,79);
                break;
            default:
                break;
        }
    }
    wrefresh(win->cursorWindow);
    wclear(win->boardWindow);
    for (i = 0; i < board->rows; i ++) {
        for (j=0; j < board->columns; j++) {
            switch(board->cells[i][j] ){
                case 0:
                    mvwaddch(win->boardWindow, i,j,42);
                    wrefresh(win->boardWindow);
                    break;
                case 1:
                    mvwaddch(win->boardWindow, i,j, 88);
                    wrefresh(win->boardWindow);
                    break;
                case 2:
                    mvwaddch(win->boardWindow, i, j, 79);
                    wrefresh(win->boardWindow);
                    break;
                default:
                    break;
            }
        }
    }
}