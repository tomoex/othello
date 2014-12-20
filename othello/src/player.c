/*
 * player.c
 *
 *  Created on: 2014/12/10
 *      Author: tomoe
 */


#include "../othello.h"

#include <stdlib.h>

//---------------------------------------------------------
// private

// Fool
void Player_fool_think(Player* player, Othello* othello, int* x, int* y, BOOL* isResign){
    // ランダムに打つ場所を決める
    int index;
    PointList list;

    Othello_moveList(othello, &list);

    if(list.length > 0){
        index = rand() % list.length;
        *x = list.x[index];
        *y = list.y[index];
        *isResign = FALSE;
    }
    else{
        *isResign = TRUE;
    }
}

// Beginner

typedef struct{
    int index;
    int evaluation;
}Evaluation;

int Player_beginner_evaluation(Player* player, Othello* othello, int color){
    int eval;
    eval = Othello_count(othello, color);
    return eval;
}

Evaluation Player_beginner_search(Player* player, Othello* othello, const PointList* list, int depth){
    Othello othelloEval;
    int i;
    Evaluation eval;

    int tempEval = 0;;
    for(i = 0; i < list->length; i++){
        // 盤面を更新する
        Othello_initialize(&othelloEval);
        Othello_copy(othello, &othelloEval);
        Othello_moveThis(&othelloEval, list->x[i], list->y[i]);

        // 評価 or 探索
        if(depth == 0){
            // 盤面を評価する
            tempEval = Player_beginner_evaluation(player, &othelloEval, othelloEval.turn);
        }
        else{
            // 探索をする
            PointList nextList;
            Othello_changeTurn(&othelloEval);

            Othello_moveList(othello, &nextList);

            if(nextList.length > 0){
                eval = Player_beginner_search(player, &othelloEval, &nextList, depth - 1);
            }
            else{
                tempEval = Player_beginner_evaluation(player, &othelloEval, othelloEval.turn);
            }
        }

        // 評価結果の判定
        if(i == 0){
            eval.index = i;
            eval.evaluation = tempEval;
        }
        else{
            if(player->color == othelloEval.who){
                // 自ターン→最大評価値を保持
                if(tempEval > eval.evaluation){
                    eval.index = i;
                    eval.evaluation = tempEval;
                }
            }
            else{
                // 相手ターン→最小評価値を保持
                if(tempEval < eval.evaluation){
                    eval.index = i;
                    eval.evaluation = tempEval;
                }
            }
        }
    }

    return eval;
}

void Player_beginner_think(Player* player, Othello* othello, int* x, int* y, BOOL* isResign){
    // 最もたくさんの数が取れる場所に打つ
    Evaluation eval;
    PointList list;

    Othello_moveList(othello, &list);

    if(list.length > 0){
        eval = Player_beginner_search(player, othello, &list, 5);

        *x = list.x[eval.index];
        *y = list.y[eval.index];
        *isResign = FALSE;
    }
    else{
        *isResign = TRUE;
    }

}


//---------------------------------------------------------
// public

void Player_npcFool(Player* player, int color){
    srand(10);
    player->color = color;
    player->think = Player_fool_think;
}

void Player_npcBeginner(Player* player, int color){
    player->color = color;
    player->think = Player_beginner_think;
}

void Player_think(Player* player, Othello* othello, int* x, int* y, BOOL* isResign){
    player->think(player, othello, x, y, isResign);
}
