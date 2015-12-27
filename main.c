/*
 * main.c
 *
 *  Created on: 2014/12/08
 *      Author: tomoe
 */


#include "common_type.h"
#include "othello.h"
#include "ui.h"


#include <stdio.h>
#include <assert.h>

int main(){
    Othello othello;
    OthelloUI ui;
    Player playerBlack;
    Player playerWhite;

    /* プレイヤー初期化 */
    Player_npcBeginner2(&playerBlack, OTHELLO_PLAYER_BLACK);
    Player_npcFool(&playerWhite, OTHELLO_PLAYER_WHITE);

    /* オセロ盤初期化 */
    Othello_initialize(&othello);

    /* プレイヤー設定 */
    Othello_configure(&othello, &playerBlack, &playerWhite);

    /* 試合終了まで交互に打つ */
    while(Othello_isGameEnd(&othello) == FALSE){
        OthelloUI_update(&ui, &othello);

        Othello_update(&othello);
    }

    /* 最終結果表示 */
    OthelloUI_update(&ui, &othello);

    return 0;
}


