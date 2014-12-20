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

    /* プレイヤー初期化 */
    Player_npcBeginner(&playerBlack, OTHELLO_PLAYER_BLACK);
    Player_npcFool(&playerWhite, OTHELLO_PLAYER_WHITE);

    /* オセロ盤初期化 */
    Othello_initialize(&othello);

    /* 試合終了まで交互に打つ */
    while(Othello_isGameEnd(&othello) == FALSE){
        OthelloUI_update(&ui, &othello);

        if(Othello_whosTurnIsNow(&othello) == OTHELLO_PLAYER_BLACK){
            Othello_move(&othello, &playerBlack);
        }
        else if(Othello_whosTurnIsNow(&othello) == OTHELLO_PLAYER_WHITE){
            Othello_move(&othello, &playerWhite);
        }
        else{
            assert(0);
        }
        Othello_updateGameEnd(&othello);
    }

    OthelloUI_update(&ui, &othello);

    return 0;
}


