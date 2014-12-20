/*
 * ui.c
 *
 *  Created on: 2014/12/10
 *      Author: tomoe
 */

#include "../ui.h"
#include <stdio.h>

void OthelloUI_update(OthelloUI* ui, Othello* othello){
    const char disc[3] = {'@', 'o', ' '};
    const char side[2] = {'b', 'w'};
    printf("=================================================\n");fflush(stdout);
    printf("turn %d, side %c, win %d\n", othello->turn, side[othello->who], othello->win);fflush(stdout);
    printf("    a   b   c   d   e   f   g   h\n");fflush(stdout);
    printf("  +---+---+---+---+---+---+---+---+\n");fflush(stdout);
    printf("1 + %c + %c + %c + %c + %c + %c + %c + %c +\n", disc[othello->board[0][0]], disc[othello->board[1][0]], disc[othello->board[2][0]], disc[othello->board[3][0]], disc[othello->board[4][0]], disc[othello->board[5][0]], disc[othello->board[6][0]], disc[othello->board[7][0]]);fflush(stdout);
    printf("  +---+---+---+---+---+---+---+---+\n");fflush(stdout);
    printf("2 + %c + %c + %c + %c + %c + %c + %c + %c +\n", disc[othello->board[0][1]], disc[othello->board[1][1]], disc[othello->board[2][1]], disc[othello->board[3][1]], disc[othello->board[4][1]], disc[othello->board[5][1]], disc[othello->board[6][1]], disc[othello->board[7][1]]);fflush(stdout);
    printf("  +---+---+---+---+---+---+---+---+\n");fflush(stdout);
    printf("3 + %c + %c + %c + %c + %c + %c + %c + %c +\n", disc[othello->board[0][2]], disc[othello->board[1][2]], disc[othello->board[2][2]], disc[othello->board[3][2]], disc[othello->board[4][2]], disc[othello->board[5][2]], disc[othello->board[6][2]], disc[othello->board[7][2]]);fflush(stdout);
    printf("  +---+---+---+---+---+---+---+---+\n");fflush(stdout);
    printf("4 + %c + %c + %c + %c + %c + %c + %c + %c +\n", disc[othello->board[0][3]], disc[othello->board[1][3]], disc[othello->board[2][3]], disc[othello->board[3][3]], disc[othello->board[4][3]], disc[othello->board[5][3]], disc[othello->board[6][3]], disc[othello->board[7][3]]);fflush(stdout);
    printf("  +---+---+---+---+---+---+---+---+\n");fflush(stdout);
    printf("5 + %c + %c + %c + %c + %c + %c + %c + %c +\n", disc[othello->board[0][4]], disc[othello->board[1][4]], disc[othello->board[2][4]], disc[othello->board[3][4]], disc[othello->board[4][4]], disc[othello->board[5][4]], disc[othello->board[6][4]], disc[othello->board[7][4]]);fflush(stdout);
    printf("  +---+---+---+---+---+---+---+---+\n");fflush(stdout);
    printf("6 + %c + %c + %c + %c + %c + %c + %c + %c +\n", disc[othello->board[0][5]], disc[othello->board[1][5]], disc[othello->board[2][5]], disc[othello->board[3][5]], disc[othello->board[4][5]], disc[othello->board[5][5]], disc[othello->board[6][5]], disc[othello->board[7][5]]);fflush(stdout);
    printf("  +---+---+---+---+---+---+---+---+\n");fflush(stdout);
    printf("7 + %c + %c + %c + %c + %c + %c + %c + %c +\n", disc[othello->board[0][6]], disc[othello->board[1][6]], disc[othello->board[2][6]], disc[othello->board[3][6]], disc[othello->board[4][6]], disc[othello->board[5][6]], disc[othello->board[6][6]], disc[othello->board[7][6]]);fflush(stdout);
    printf("  +---+---+---+---+---+---+---+---+\n");fflush(stdout);
    printf("8 + %c + %c + %c + %c + %c + %c + %c + %c +\n", disc[othello->board[0][7]], disc[othello->board[1][7]], disc[othello->board[2][7]], disc[othello->board[3][7]], disc[othello->board[4][7]], disc[othello->board[5][7]], disc[othello->board[6][7]], disc[othello->board[7][7]]);fflush(stdout);
    printf("  +---+---+---+---+---+---+---+---+\n");fflush(stdout);
    printf("black %d, white %d\n", Othello_count(othello, OTHELLO_BOARD_BLACK), Othello_count(othello, OTHELLO_BOARD_WHITE));fflush(stdout);
    fflush(stdout);
}

