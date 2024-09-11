#ifndef PLAYER_H
#define PLAYER_H

#include "MapChip.h"

class Player {
public:
    static const int PLAYER_SIZE = MapChip::CHIP_SIZE;  // プレイヤーのサイズ（32x32）
    static const int MOVE_SPEED = 4;                    // プレイヤーの移動速度
    static const int JUMP_POWER = -15;                  // ジャンプ力
    static const int MAX_FALL_SPEED = 10;               // 最大落下速度
    static const int MAX_JUMPS = 3;                     // 空中ジャンプの最大回数
    static const int JUMP_COOLDOWN = 10;                // ジャンプクールタイムフレーム

    Player(int startX, int startY, MapChip* map);  // コンストラクタ
    ~Player();  // デストラクタ

    // プレイヤーの描画
    void Draw();
    // プレイヤーの更新（移動、ジャンプ、落下）
    void Update();

private:
    int x, y;             // プレイヤーの位置
    int vx, vy;           // プレイヤーの速度（vx: 水平速度, vy: 垂直速度）
    int jumpsLeft;        // 残りジャンプ回数
    int jumpCooldown;     // ジャンプクールタイム
    bool isOnGround;      // プレイヤーが地面にいるかどうか
    int texture;          // プレイヤーのテクスチャ
    int playerFlag = true;
    MapChip* map;         // マップへのポインタ（当たり判定に使用）

    // 当たり判定をチェックする
    bool CheckCollision(int nextX, int nextY);
    // プレイヤーの下に地面があるかを確認する
    bool IsOnGround();
    // テクスチャを読み込む
    void LoadTexture();
    // テクスチャを解放する
    void UnloadTexture();
};

#endif // PLAYER_H
