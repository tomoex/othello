/*
 * othello.h
 *
 *  Created on: 2014/12/10
 *      Author: tomoe
 */

#ifndef OTHELLO_H_
#define OTHELLO_H_

#include "../common_type.h"

enum{
    OTHELLO_PLAYER_BLACK = 0,
    OTHELLO_PLAYER_WHITE = 1
};

enum{
    OTHELLO_BOARD_BLACK,
    OTHELLO_BOARD_WHITE,
    OTHELLO_BOARD_NONE
};

enum{
    OTHELLO_WINNER_BLACK,
    OTHELLO_WINNER_WHITE,
    OTHELLO_WINNER_DRAW,
    OTHELLO_WINNER_NONE
};


#define OTHELLO_X_MAX 8
#define OTHELLO_Y_MAX 8

/*
 *     x[0]x[1]x[2]x[3]x[4]x[5]x[6]x[7]
 *     +---+---+---+---+---+---+---+---+
 * y[0]|   |   |   |   |   |   |   |   |
 *     +---+---+---+---+---+---+---+---+
 * y[1]|   |   |   |   |   |   |   |   |
 *     +---+---+---+---+---+---+---+---+
 * y[2]|   |   |   |   |   |   |   |   |
 *     +---+---+---+---+---+---+---+---+
 * y[3]|   |   |   |   |   |   |   |   |
 *     +---+---+---+---+---+---+---+---+
 * y[4]|   |   |   |   |   |   |   |   |
 *     +---+---+---+---+---+---+---+---+
 * y[5]|   |   |   |   |   |   |   |   |
 *     +---+---+---+---+---+---+---+---+
 * y[6]|   |   |   |   |   |   |   |   |
 *     +---+---+---+---+---+---+---+---+
 * y[7]|   |   |   |   |   |   |   |   |
 *     +---+---+---+---+---+---+---+---+
 *
 */
typedef struct{
    int who;
    int turn;
    int board[OTHELLO_X_MAX][OTHELLO_Y_MAX];
    int win;
}Othello;

struct PlayerType;

typedef struct PlayerType{
    int color;
    void (*think)(struct PlayerType*, Othello*, int*, int*, BOOL*);
}Player;

#define POINT_LIST_CAPACITY 64
typedef struct{
    int length;
    int x[POINT_LIST_CAPACITY];
    int y[POINT_LIST_CAPACITY];
}PointList;

/* 初期化 */
void Othello_initialize(Othello* othello);

/* コピー */
void Othello_copy(const Othello* src, Othello* dist);

/* 試合が終了しているか？ */
BOOL Othello_isGameEnd(const Othello* othello);

/* 黒と白のどちらの手番か？ */
int Othello_turn(const Othello* othello);

/* 現在の手番のプレイヤーが打つ */
void Othello_move(Othello* othello, Player* player);

/* 両者ともに打てる場所がないか？ */
BOOL Othello_isNotMoveAll(const Othello* othello);

/* 打てる場所があるか？ */
BOOL Othello_isMoveSomewhere(const Othello* othello);

/* その場所に打てるか？ */
BOOL Othello_isMoveThis(const Othello* othello, int x, int y);

/* 打てる場所の一覧を取得する */
int Othello_moveList(const Othello* othello, PointList* list);

/* 勝者判定をする */
void Othello_updateWinner(Othello* othello);

/* 黒 or 白の色の数を取得する */
int Othello_count(Othello* othello, int color);

/* 打つ */
void Othello_moveThis(Othello* othello, int x, int y);
/* 手番を次に変更する */
void Othello_change(Othello* othello);




void Player_npcFool(Player* player, int color);

void Player_npcBeginner(Player* player, int color);

/* 打つ場所を考えて決める */
void Player_think(Player* player, Othello* othello, int* x, int* y, BOOL* isResign);


void PointList_initialize(PointList* pointList);

void PointList_Append(PointList* pointList, int x, int y);

void PointList_AppendList(PointList* pointList, const PointList* sourceList);

#endif /* OTHELLO_H_ */
