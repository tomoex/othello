/*
 * player.c
 *
 *  Created on: 2014/12/10
 *      Author: tomoe
 */


#include "othello.h"
#include "array.h"

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

// Beginner2


void nextBoardList(const Othello* othello, PointList* points, BoardList* boards){
    Othello othelloTemp;
    int i;

    // 現在の盤面状態において、次にとり得るすべての盤面を計算してBoardListに入れる
    Othello_moveList(othello, points);

    BoardList_initialize(boards);
    for(i = 0; i < points->length; i++){
        Othello_initialize(&othelloTemp);
        Othello_copy(othello, &othelloTemp);
        Othello_moveThis(&othelloTemp, points->x[i], points->y[i]);

        BoardList_Append(boards, Othello_board(&othelloTemp));
    }
}

int evalBoard(const Board* board, int color){
    int x;
    int y;
    int eval = 0;

    for(x = 0; x < OTHELLO_X_MAX; x++){
        for(y = 0; y < OTHELLO_Y_MAX; y++){
            if(Board_get(board, x, y) == color){
                eval++;
            }
        }
    }

    return eval;
}

void evalBoardList(const Othello* othello, const BoardList* boards, int evals[]){
    int i;
    for(i = 0; i < boards->length; i++){
        evals[i] = evalBoard(&(boards->boards[i]), Othello_whosTurnIsNow(othello));
    }
}


Evaluation Player_beginner2_search(Player* player, Othello* othello, const PointList* list, int depth){
    Evaluation eval;
    PointList points;
    BoardList boards;
    int evals[BOARD_LIST_CAPACITY];
    int tempEval = 0;
    int i;

    nextBoardList(othello, &points, &boards);
    evalBoardList(othello, &boards, evals);

    for(i = 0; i < boards.length; i++){
        // 最大評価値を保持
        if(tempEval < evals[i]){
            tempEval = evals[i];
            eval.index = i;
            eval.evaluation = tempEval;
        }
    }

    return eval;
}

void Player_beginner2_think(Player* player, Othello* othello, int* x, int* y, BOOL* isResign){
    // 最もたくさんの数が取れる場所に打つ
    Evaluation eval;
    PointList list;

    Othello_moveList(othello, &list);

    if(list.length > 0){
        eval = Player_beginner2_search(player, othello, &list, 5);

        *x = list.x[eval.index];
        *y = list.y[eval.index];
        *isResign = FALSE;
    }
    else{
        *isResign = TRUE;
    }

    {
        Array int_array;
        int temp;
        int temp_out;
        int i;
        Array_new(&int_array, 5, sizeof(int));
        temp = 0; Array_append(&int_array, &temp);
        temp = 1; Array_append(&int_array, &temp);
        temp = 2; Array_append(&int_array, &temp);
        temp = 3; Array_append(&int_array, &temp);
        temp = 4; Array_append(&int_array, &temp);
        temp = 5; Array_append(&int_array, &temp);

        for(i = 0; i < Array_length(&int_array); i++){
            temp_out = *(int*)Array_get(&int_array, i);
        }
        Array_delete(&int_array);
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

void Player_npcBeginner2(Player* player, int color){
    player->color = color;
    player->think = Player_beginner2_think;
}

void Player_think(Player* player, Othello* othello, int* x, int* y, BOOL* isResign){
    player->think(player, othello, x, y, isResign);
}
