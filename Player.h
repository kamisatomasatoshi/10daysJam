#ifndef PLAYER_H
#define PLAYER_H

#include "MapChip.h"

class Player {
public:
    static const int PLAYER_WIDTH = MapChip::CHIP_SIZE;       // プレイヤーの幅
    static const int PLAYER_HEIGHT = MapChip::CHIP_SIZE * 2;  // プレイヤーの高さ（縦に2ブロック分）
    static const int MOVE_SPEED = 4;                          // プレイヤーの移動速度

    Player(int startX, int startY, MapChip* map);  // コンストラクタ
    ~Player();  // デストラクタ

    // プレイヤーの描画
    void Draw();
    // プレイヤーの更新（移動）
    void Update();

private:
    int x, y;         // プレイヤーの位置
    int texture;      // プレイヤーのテクスチャ
    MapChip* map;     // マップへのポインタ（当たり判定に使用）

    // 当たり判定をチェックする
    bool CheckCollision(int nextX, int nextY);
    // テクスチャを読み込む
    void LoadTexture();
    // テクスチャを解放する
    void UnloadTexture();
};

#endif // PLAYER_H
