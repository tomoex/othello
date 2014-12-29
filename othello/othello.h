/**
 * @file othello.h
 * @brief オセロライブラリ
 */

#ifndef OTHELLO_H_
#define OTHELLO_H_

#include "common_type.h"


/*---------------------------------------------------------------
 * 構造体のプロトタイプ宣言
 *--------------------------------------------------------------*/
struct Player_t;
typedef struct Player_t Player;


struct PointList_t;
typedef struct PointList_t PointList;



/***************************************************************************************************
 * オセロ
 ***************************************************************************************************/
#define OTHELLO_X_MAX 8     //! 盤面の横方向のマス目の数
#define OTHELLO_Y_MAX 8     //! 盤面の縦方向のマス目の数

/**
 * オセロ構造体
 *
 * 盤面と試合の状態を保持する。
 *
 * 盤面は左上をx,y = 0,0として表す
 *
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
    int who;                                        //! 現在のターンで打つプレイヤーの種別
    int turn;                                       //! 現在のターン数。初期状態を0ターン目とする
    int board[OTHELLO_X_MAX][OTHELLO_Y_MAX];        //! 盤面
    int win;                                        //! 試合の勝者
}Othello;


/*--------------------------------------------------------------------------------------------------
 * 定数
 *-------------------------------------------------------------------------------------------------*/

/**
 * プレイヤー種別
 */
enum{
    OTHELLO_PLAYER_BLACK = 0,   //! 黒
    OTHELLO_PLAYER_WHITE = 1    //! 白
};

/**
 * 盤面の各マスの状態
 */
enum{
    OTHELLO_BOARD_BLACK,    //! 黒石がある
    OTHELLO_BOARD_WHITE,    //! 白石がある
    OTHELLO_BOARD_NONE      //! 何も置かれていない
};

/**
 * 試合の勝者
 */
enum{
    OTHELLO_WINNER_BLACK,   //! 黒の勝利
    OTHELLO_WINNER_WHITE,   //! 白の勝利
    OTHELLO_WINNER_DRAW,    //! 引き分け
    OTHELLO_WINNER_NONE     //! 勝敗が決まっていない
};

/*--------------------------------------------------------------------------------------------------
 * オブジェクト操作系
 *-------------------------------------------------------------------------------------------------*/

/**
 *  初期化する
 *
 *  盤面に白黒それぞれ2個ずつ配置し、試合開始の状態に初期化する。
 *
 *  @param[out] othello 対象のインスタンス
 */
void Othello_initialize(Othello* othello);

/** オブジェクトをコピーする
 *
 * @param[in]  src  コピー元
 * @param[out] dist コピー先
 */
void Othello_copy(const Othello* src, Othello* dist);

/*--------------------------------------------------------------------------------------------------
 * 石を打つ
 *-------------------------------------------------------------------------------------------------*/

/** 両者ともに打てる場所が一切ないか？
 *
 * 盤面が埋まる、挟める場所がないなどで、打てる場所が存在しないかどうかを判定して返す。
 *
 * @param[in] othello 対象のインスタンス
 *
 * @retval TRUE  黒も白も打てない
 * @retval FALSE 黒か白のいずれかが打てる
 */
BOOL Othello_isNotMoveAll(const Othello* othello);

/**
 *  打てる場所があるか？
 *
 *  現在のターンのプレイヤーが打てる場所があるかどうかを判定して返す。
 *
 *  @param[in] othello 対象のインスタンス
 *
 *  @retval TRUE  打てる場所がある
 *  @retval FALSE 打てる場所がない
 */
BOOL Othello_isMoveSomewhere(const Othello* othello);

/**
 * この場所に打てるか？
 *
 * オセロのルール上、x,yで指定した座標に現在のターンのプレイヤーが打つことができるかを判定して返す。
 *
 * @param[in] othello 対象のインスタンス
 * @paran[in] x       x座標(0～OTHELLO_X_MAX-1)
 * @paran[in] y       y座標(0～OTHELLO_Y_MAX-1)
 *
 * @retval TRUE  打てる
 * @retval FALSE 打てない
 */
BOOL Othello_isMoveThis(const Othello* othello, int x, int y);

/** 打てる場所の一覧を取得する
 *
 * 現在のターンのプレイヤーが打つことができる座標すべてを判定し、引数で指定したアドレスに書き込む。
 *
 * @param[in]  othello 対象のインスタンス
 * @param[out] list    出力用の座標リストのアドレス
 */
int Othello_moveList(const Othello* othello, PointList* list);

/** この場所に打つ
 *
 * 現在のターンのプレイヤーが引数で指定した座標に打つ。
 *
 * @param[in,out] othello 対象のインスタンス
 * @paran[in]     x       x座標(0～OTHELLO_X_MAX-1)
 * @paran[in]     y       y座標(0～OTHELLO_Y_MAX-1)
 */
void Othello_moveThis(Othello* othello, int x, int y);

/**
 *  現在のターンのプレイヤーが打つ
 *
 *  Playerオブジェクトの判断により打つ座標を決定し、各種打つ系機能を実行する。
 *
 *  @param[in,out] othello 対象のインスタンス
 *  @param[in,out] player  現在のターンのプレイヤー
 */
void Othello_move(Othello* othello, Player* player);

/*--------------------------------------------------------------------------------------------------
 * 試合状態制御
 *-------------------------------------------------------------------------------------------------*/

/**
 * 黒と白のどちらのターンか？
 *
 * @param[in] othello 対象のインスタンス
 *
 * @retval OTHELLO_PLAYER_BLACK 黒のターン
 * @retval OTHELLO_PLAYER_WHITE 白のターン
 */
int Othello_whosTurnIsNow(const Othello* othello);

/** 試合が終了しているか？
 *
 * @param[in] othello 対象のインスタンス
 *
 * 白 or 黒のプレイヤーの勝利、もしくは引き分けが決定していれば試合終了、それ意外の場合は終了していないと判定して返す。
 *
 * @retval TRUE  試合終了している
 * @retval FALSE 試合終了していない
 */
BOOL Othello_isGameEnd(const Othello* othello);

/** 試合終了判定をする
 *
 * 両方のプレイヤーが打てる場所がなくなった場合に勝敗を更新する。
 * いずれかのプレイヤーが継続して打てる場合は何もしない。
 *
 * @param[in,out]  othello 対象のインスタンス
 */
void Othello_updateGameEnd(Othello* othello);

/** ターンを次に変更する
 *
 * 現在のプレイヤーのターンを終了し、次のターンにする。
 *
 * @param[in,out] othello 対象のインスタンス
 */
void Othello_changeTurn(Othello* othello);

/*--------------------------------------------------------------------------------------------------
 * その他
 *-------------------------------------------------------------------------------------------------*/

/** 黒 or 白 or 置かれていないマスの数を取得する
 *
 * 引数で指定したマスの状態の数をカウントして返す。
 *
 * @param[in]  othello 対象のインスタンス
 * @param[in]  color   黒(OTHELLO_BOARD_BLACK) or 白(OTHELLO_BOARD_WHITE) or 置かれていない(OTHELLO_BOARD_NONE)
 *
 * @return カウント数
 */
int Othello_count(const Othello* othello, int color);

/***************************************************************************************************
 * 座標リスト
 ***************************************************************************************************/
#define POINT_LIST_CAPACITY 64      //! PointListに格納可能な座標の最大数

/**
 * オセロ盤面の座標リスト
 */
struct PointList_t{
    int length;                     //! 有効な座標数
    int x[POINT_LIST_CAPACITY];     //! x座標
    int y[POINT_LIST_CAPACITY];     //! y座標
};

/*--------------------------------------------------------------------------------------------------
 * リスト操作
 *-------------------------------------------------------------------------------------------------*/

/**
 * 座標リストを初期化する
 *
 * @param[out]  pointList 対象のインスタンス
 */
void PointList_initialize(PointList* pointList);

/**
 * 座標リストに座標を追加する
 *
 * 既存要素の末尾に引数で指定した座標を追加する。最大容量(POINT_LIST_CAPACITY)を超えた追加は無視される。
 *
 * @param[in,out]  pointList 対象のインスタンス
 * @param[in]      x         追加するx座標
 * @param[in]      y         追加するy座標
 */
void PointList_Append(PointList* pointList, int x, int y);

/**
 * 座標リストを連結する
 *
 * dest側の末尾にsrc側の要素を追加する。最大容量(POINT_LIST_CAPACITY)を超えた要素は破棄される。
 *
 * @param[in,out]  destList   対象のインスタンス
 * @param[in]      sourceList 対象のインスタンス
 */
void PointList_AppendList(PointList* destList, const PointList* sourceList);


/***************************************************************************************************
 * プレイヤー
 ***************************************************************************************************/
/**
 * オセロのプレイヤー
 */
struct Player_t{
    int color;                                                              //! プレイヤーの種別
    void (*think)(struct Player_t*, Othello*, int*, int*, BOOL*);         //! 自ターンで「打つ」処理を行う関数のポインタ
};


/*--------------------------------------------------------------------------------------------------
 * 初期設定
 *-------------------------------------------------------------------------------------------------*/

/**
 * 無能な思考ルーチンを持つプレイヤーを設定する
 *
 * @param[out]  player 対象のインスタンス
 * @param[in]   color  黒(OTHELLO_PLAYER_BLACK) or 白(OTHELLO_PLAYER_WHITE)
 */
void Player_npcFool(Player* player, int color);

/**
 * 初心者レベル思考ルーチンを持つプレイヤーを設定する
 *
 * @param[out]  player 対象のインスタンス
 * @param[in]   color  黒(OTHELLO_PLAYER_BLACK) or 白(OTHELLO_PLAYER_WHITE)
 */
void Player_npcBeginner(Player* player, int color);

/*--------------------------------------------------------------------------------------------------
 * 思考ルーチン
 *-------------------------------------------------------------------------------------------------*/

/** 打つ場所を考えて決める
 *
 * @param[in,out]  player   対象のインスタンス
 * @param[in]      othello  オセロ
 * @param[out]     x        打つx座標を格納するアドレス
 * @param[out]     y        打つx座標を格納するアドレス
 * @param[out]     isResign 投了するかどうか(TRUE:する, FALSE:しない)を格納するアドレス
 */
void Player_think(Player* player, Othello* othello, int* x, int* y, BOOL* isResign);


#endif /* OTHELLO_H_ */
