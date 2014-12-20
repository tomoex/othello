/*
 * main.c
 *
 *  Created on: 2014/12/08
 *      Author: tomoe
 */


#include "common_type.h"
#include "othello/othello.h"
#include "ui/ui.h"


#include <stdio.h>
#include <assert.h>

int main(){
    Othello othello;
    OthelloUI ui;
    Player playerBlack;
    Player playerWhite;

    Player_npcBeginner(&playerBlack, OTHELLO_PLAYER_BLACK);
    Player_npcFool(&playerWhite, OTHELLO_PLAYER_WHITE);

    Othello_initialize(&othello);

    while(Othello_isGameEnd(&othello) == FALSE){
        OthelloUI_update(&ui, &othello);

        if(Othello_turn(&othello) == OTHELLO_PLAYER_BLACK){
            Othello_move(&othello, &playerBlack);
        }
        else if(Othello_turn(&othello) == OTHELLO_PLAYER_WHITE){
            Othello_move(&othello, &playerWhite);
        }
        else{
            assert(0);
        }
        Othello_updateWinner(&othello);
    }

    OthelloUI_update(&ui, &othello);

    return 0;
}


