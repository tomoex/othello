/*
 * othello.c
 *
 *  Created on: 2014/12/10
 *      Author: tomoe
 */

#include "../othello.h"
#include <stddef.h>
#include <string.h>
#include <assert.h>

//---------------------------------------------------------
// private

/* 負けを宣言する */
void Othello_loose(Othello* othello);
/* (可能なら)手番をパスする */
void Othello_pass(Othello* othello);
/* 裏返す */
void Othello_reverse(Othello* othello, int x, int y);


enum{
    REVERSE_DIR_LEFT,
    REVERSE_DIR_RIGHT,
    REVERSE_DIR_UP,
    REVERSE_DIR_DOWN,
    REVERSE_DIR_NONE
};

int Othello_countOfReverse(const Othello* othello, int x, int y, int me, int opponent, PointList* reverseList, int UpDown, int RightLeft){
    int x_;
    int y_;
    int reverse = 0;
    BOOL isOutflank = FALSE;
    PointList tempList;

    PointList_initialize(&tempList);

    // 初期化
    if(UpDown == REVERSE_DIR_UP){
        y_ = y - 1;
    }
    else if(UpDown == REVERSE_DIR_DOWN){
        y_ = y + 1;
    }
    else if(UpDown == REVERSE_DIR_NONE){
        y_ = y;
    }
    else{
        assert(0);
    }

    if(RightLeft == REVERSE_DIR_RIGHT){
        x_ = x + 1;
    }
    else if(RightLeft == REVERSE_DIR_LEFT){
        x_ = x - 1;
    }
    else if(RightLeft == REVERSE_DIR_NONE){
        x_ = x;
    }
    else{
        assert(0);
    }

    while(1){
        // ループのbreak
        if(UpDown == REVERSE_DIR_UP){
            if(y_ < 0){
                break;
            }
        }
        else if(UpDown == REVERSE_DIR_DOWN){
            if(y_ >= OTHELLO_Y_MAX){
                break;
            }
        }

        if(RightLeft == REVERSE_DIR_RIGHT){
            if(x_ >= OTHELLO_X_MAX){
                break;
            }
        }
        else if(RightLeft == REVERSE_DIR_LEFT){
            if(x_ < 0){
                break;
            }
        }

        // 裏返し判定
        if(othello->board[x_][y_] == opponent){
            // 相手の色が連続して存在→次の位置を判定
            reverse++;
            PointList_Append(&tempList, x_, y_);
        }
        else if(othello->board[x_][y_] == me){
            // 自分の色が存在→挟めているかチェックしbreak
            if(reverse > 0){
                isOutflank = TRUE;
                break;
            }
            else{
                isOutflank = FALSE;
                break;
            }
        }
        else{
            // ディスクが置かれていない→挟めていないとしてbreak
            isOutflank = FALSE;
            break;
        }

        // カウンタインクリメント
        if(UpDown == REVERSE_DIR_UP){
            y_--;
        }
        else if(UpDown == REVERSE_DIR_DOWN){
            y_++;
        }

        if(RightLeft == REVERSE_DIR_RIGHT){
            x_++;
        }
        else if(RightLeft == REVERSE_DIR_LEFT){
            x_--;
        }
    }

    if(isOutflank == FALSE){
        // 裏返せるディスクがない
        reverse = 0;
    }
    else{
        // 裏返せるディスクがある
        if(reverseList != NULL){
            int i;
            for(i = 0; i < tempList.length; i++){
                PointList_Append(reverseList, tempList.x[i], tempList.y[i]);
            }
        }
    }

    return reverse;
}

int Othello_countOfReverseLeft(const Othello* othello, int x, int y, int me, int opponent, PointList* reverseList){
    return Othello_countOfReverse(othello, x, y, me, opponent, reverseList, REVERSE_DIR_NONE, REVERSE_DIR_LEFT);
}

int Othello_countOfReverseRight(const Othello* othello, int x, int y, int me, int opponent, PointList* reverseList){
    return Othello_countOfReverse(othello, x, y, me, opponent, reverseList, REVERSE_DIR_NONE, REVERSE_DIR_RIGHT);
}

int Othello_countOfReverseUp(const Othello* othello, int x, int y, int me, int opponent, PointList* reverseList){
    return Othello_countOfReverse(othello, x, y, me, opponent, reverseList, REVERSE_DIR_UP, REVERSE_DIR_NONE);
}

int Othello_countOfReverseDown(const Othello* othello, int x, int y, int me, int opponent, PointList* reverseList){
    return Othello_countOfReverse(othello, x, y, me, opponent, reverseList, REVERSE_DIR_DOWN, REVERSE_DIR_NONE);
}

int Othello_countOfReverseLeftUp(const Othello* othello, int x, int y, int me, int opponent, PointList* reverseList){
    return Othello_countOfReverse(othello, x, y, me, opponent, reverseList, REVERSE_DIR_UP, REVERSE_DIR_LEFT);
}

int Othello_countOfReverseLeftDown(const Othello* othello, int x, int y, int me, int opponent, PointList* reverseList){
    return Othello_countOfReverse(othello, x, y, me, opponent, reverseList, REVERSE_DIR_DOWN, REVERSE_DIR_LEFT);
}

int Othello_countOfReverseRightUp(const Othello* othello, int x, int y, int me, int opponent, PointList* reverseList){
    return Othello_countOfReverse(othello, x, y, me, opponent, reverseList, REVERSE_DIR_UP, REVERSE_DIR_RIGHT);
}

int Othello_countOfReverseRightDown(const Othello* othello, int x, int y, int me, int opponent, PointList* reverseList){
    return Othello_countOfReverse(othello, x, y, me, opponent, reverseList, REVERSE_DIR_DOWN, REVERSE_DIR_RIGHT);
}

void Othello_reverse(Othello* othello, int x, int y){
    int me;
    int opponent;
    PointList list;
    int count = 0;
    int i;

    // 手番取得
    if(Othello_turn(othello) == OTHELLO_PLAYER_BLACK){
        me       = OTHELLO_BOARD_BLACK;
        opponent = OTHELLO_BOARD_WHITE;
    }
    else if(Othello_turn(othello) == OTHELLO_PLAYER_WHITE){
        me       = OTHELLO_BOARD_WHITE;
        opponent = OTHELLO_BOARD_BLACK;
    }
    else{
        assert(0);
    }

    // 裏返すディスクを調べる
    PointList_initialize(&list);
    count += Othello_countOfReverseLeft(othello, x, y, me, opponent, &list);
    count += Othello_countOfReverseRight(othello, x, y, me, opponent, &list);
    count += Othello_countOfReverseUp(othello, x, y, me, opponent, &list);
    count += Othello_countOfReverseDown(othello, x, y, me, opponent, &list);
    count += Othello_countOfReverseLeftUp(othello, x, y, me, opponent, &list);
    count += Othello_countOfReverseLeftDown(othello, x, y, me, opponent, &list);
    count += Othello_countOfReverseRightUp(othello, x, y, me, opponent, &list);
    count += Othello_countOfReverseRightDown(othello, x, y, me, opponent, &list);

    // 裏返す
    for(i = 0; i < list.length; i++){
        othello->board[list.x[i]][list.y[i]] = me;
    }
}

void Othello_loose(Othello* othello){
    if(Othello_turn(othello) == OTHELLO_PLAYER_BLACK){
        othello->win = OTHELLO_WINNER_WHITE;
    }
    else if(Othello_turn(othello) == OTHELLO_PLAYER_WHITE){
        othello->win = OTHELLO_WINNER_BLACK;
    }
    else{
        assert(0);
    }
}

void Othello_pass(Othello* othello){
    Othello_change(othello);
}



//---------------------------------------------------------
// public

void Othello_initialize(Othello* othello){
    int x, y;

    othello->who  = OTHELLO_PLAYER_BLACK;
    othello->turn = 0;
    othello->win  = OTHELLO_WINNER_NONE;

    for(x = 0; x < OTHELLO_X_MAX; x++){
        for(y = 0; y < OTHELLO_Y_MAX; y++){
            othello->board[x][y] = OTHELLO_BOARD_NONE;
        }
    }
    othello->board[3][3] = OTHELLO_BOARD_WHITE;
    othello->board[4][4] = OTHELLO_BOARD_WHITE;
    othello->board[3][4] = OTHELLO_BOARD_BLACK;
    othello->board[4][3] = OTHELLO_BOARD_BLACK;
}

void Othello_copy(const Othello* src, Othello* dist){
    memcpy(dist, src, sizeof(Othello));
}

BOOL Othello_isGameEnd(const Othello* othello){
    if(othello->win != OTHELLO_WINNER_NONE){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

int Othello_turn(const Othello* othello){
    return othello->who;
}

void Othello_move(Othello* othello, Player* player){
    int x;
    int y;
    BOOL isResign;

    // パス
    if(Othello_isMoveSomewhere(othello) == FALSE){
        Othello_pass(othello);
        return;
    }

    // 思考
    Player_think(player, othello, &x, &y, &isResign);

    // 投了
    if(isResign != FALSE){
        Othello_loose(othello);
        return;
    }

    // 打つ
    if(Othello_isMoveThis(othello, x, y) != FALSE){
        Othello_moveThis(othello, x, y);
        Othello_change(othello);
    }
    else{
        // TODO 無限ループ対策が必要
        Othello_move(othello, player);
    }
}

void Othello_moveThis(Othello* othello, int x, int y){
    if(Othello_isMoveThis(othello, x, y) != FALSE){
        int disc;
        if(Othello_turn(othello) == OTHELLO_PLAYER_BLACK){
            disc = OTHELLO_BOARD_BLACK;
        }
        else if(Othello_turn(othello) == OTHELLO_PLAYER_WHITE){
            disc = OTHELLO_BOARD_WHITE;
        }
        else{
            assert(0);
        }
        // 裏返す
        Othello_reverse(othello, x, y);
        // 打つ
        othello->board[x][y] = disc;
    }

}

BOOL Othello_isMoveThis(const Othello* othello, int x, int y){
    int me;
    int opponent;
    int count = 0;
    if(Othello_turn(othello) == OTHELLO_PLAYER_BLACK){
        me       = OTHELLO_BOARD_BLACK;
        opponent = OTHELLO_BOARD_WHITE;
    }
    else if(Othello_turn(othello) == OTHELLO_PLAYER_WHITE){
        me       = OTHELLO_BOARD_WHITE;
        opponent = OTHELLO_BOARD_BLACK;
    }
    else{
        assert(0);
    }

    if(othello->board[x][y] == OTHELLO_BOARD_NONE){
        count += Othello_countOfReverseLeft(othello, x, y, me, opponent, NULL);
        count += Othello_countOfReverseRight(othello, x, y, me, opponent, NULL);
        count += Othello_countOfReverseUp(othello, x, y, me, opponent, NULL);
        count += Othello_countOfReverseDown(othello, x, y, me, opponent, NULL);
        count += Othello_countOfReverseLeftUp(othello, x, y, me, opponent, NULL);
        count += Othello_countOfReverseLeftDown(othello, x, y, me, opponent, NULL);
        count += Othello_countOfReverseRightUp(othello, x, y, me, opponent, NULL);
        count += Othello_countOfReverseRightDown(othello, x, y, me, opponent, NULL);
    }
    else{
        count = 0;
    }

    if(count > 0){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

void Othello_change(Othello* othello){
    othello->turn++;
    if(Othello_turn(othello) == OTHELLO_PLAYER_BLACK){
        othello->who = OTHELLO_PLAYER_WHITE;
    }
    else if(Othello_turn(othello) == OTHELLO_PLAYER_WHITE){
        othello->who = OTHELLO_PLAYER_BLACK;
    }
    else{
        assert(0);
    }
}


void Othello_updateWinner(Othello* othello){
    int countBlack, countWhite;
    countBlack = Othello_count(othello, OTHELLO_BOARD_BLACK);
    countWhite = Othello_count(othello, OTHELLO_BOARD_WHITE);

    if(othello->win == OTHELLO_WINNER_NONE){
        if(countBlack == 0){
            // 黒がない
            othello->win = OTHELLO_WINNER_WHITE;
        }else if(countWhite == 0){
            // 白がない
            othello->win = OTHELLO_WINNER_BLACK;
        }
        else if(Othello_isNotMoveAll(othello) != FALSE){
            // 打てる場所がない(すべての盤面が埋まっている or 両者ともにパスしかできない)

            if(countBlack > countWhite){
                // 黒が多い
                othello->win = OTHELLO_WINNER_BLACK;
            }
            else if(countBlack < countWhite){
                // 白が多い
                othello->win = OTHELLO_WINNER_WHITE;
            }
            else if(countBlack == countWhite){
                // 白と黒が同数
                othello->win = OTHELLO_WINNER_DRAW;
            }
            else{
                assert(0);
            }
        }
    }
}

int Othello_count(Othello* othello, int color){
    int x, y;
    int count = 0;
    for(x = 0; x < OTHELLO_X_MAX; x++){
        for(y = 0; y < OTHELLO_Y_MAX; y++){
            if(othello->board[x][y] == color){
                count++;
            }
        }
    }

    return count;
}


BOOL Othello_isNotMoveAll(const Othello* othello){
    BOOL isMoveNow, isMoveNext;
    Othello tempOthello;
    Othello_initialize(&tempOthello);
    Othello_copy(othello, &tempOthello);

    // 今の手番のプレイヤーに打てる場所があるか？
    isMoveNow = Othello_isMoveSomewhere(&tempOthello);
    // もう片方のプレイヤーに打てる場所があるか？
    Othello_change(&tempOthello);
    isMoveNext = Othello_isMoveSomewhere(&tempOthello);

    if(isMoveNow == FALSE && isMoveNext == FALSE){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

BOOL Othello_isMoveSomewhere(const Othello* othello){
    int x, y;
    BOOL isMove;
    for(x = 0; x < OTHELLO_X_MAX; x++){
        for(y = 0; y < OTHELLO_Y_MAX; y++){
            isMove = Othello_isMoveThis(othello, x, y);
            if(isMove != FALSE){
                return TRUE;
            }
        }
    }

    return FALSE;
}

int Othello_moveList(const Othello* othello, PointList* list){
    int x, y;

    PointList_initialize(list);

    for(x = 0; x < OTHELLO_X_MAX; x++){
        for(y = 0; y < OTHELLO_Y_MAX; y++){
            if(Othello_isMoveThis(othello, x, y) != FALSE){
                PointList_Append(list, x, y);
            }
        }
    }

    if(list->length > 0){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

void PointList_initialize(PointList* pointList){
    pointList->length = 0;
}

void PointList_Append(PointList* pointList, int x, int y){
    if(pointList->length < POINT_LIST_CAPACITY){
        pointList->x[pointList->length] = x;
        pointList->y[pointList->length] = y;
        pointList->length++;
    }
}

void PointList_AppendList(PointList* pointList, const PointList* sourceList){
    int i;
    for(i = 0; i < sourceList->length; i++){
        PointList_Append(pointList, sourceList->x[i], sourceList->y[i]);
    }
}

