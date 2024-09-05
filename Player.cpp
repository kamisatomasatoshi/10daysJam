#include "Player.h"
#include "DxLib.h"

// コンストラクタ
Player::Player(int startX, int startY, MapChip* map)
    : x(startX), y(startY), map(map) {
    LoadTexture(); // プレイヤーのテクスチャを読み込む
}

// デストラクタ
Player::~Player() {
    UnloadTexture(); // プレイヤーのテクスチャを解放
}

// テクスチャを読み込む
void Player::LoadTexture() {
    texture = LoadGraph("player.png"); // プレイヤーのテクスチャ
    if (texture == -1) {
        printfDx("プレイヤーのテクスチャの読み込みに失敗しました。\n");
    }
}

// テクスチャを解放する
void Player::UnloadTexture() {
    DeleteGraph(texture);
}

// プレイヤーの描画
void Player::Draw() {
    DrawGraph(x, y, texture, TRUE);
}

// プレイヤーの更新（移動）
void Player::Update() {
    int nextX = x, nextY = y;

    // W: 上に移動
    if (CheckHitKey(KEY_INPUT_W)) {
        nextY -= MOVE_SPEED;
    }
    // A: 左に移動
    if (CheckHitKey(KEY_INPUT_A)) {
        nextX -= MOVE_SPEED;
    }
    // S: 下に移動
    if (CheckHitKey(KEY_INPUT_S)) {
        nextY += MOVE_SPEED;
    }
    // D: 右に移動
    if (CheckHitKey(KEY_INPUT_D)) {
        nextX += MOVE_SPEED;
    }

    // 当たり判定をチェック
    if (!CheckCollision(nextX, nextY)) {
        x = nextX;
        y = nextY;
    }
}

// 当たり判定をチェックする
bool Player::CheckCollision(int nextX, int nextY) {
    // プレイヤーの4隅をチェック
    int left = nextX;
    int right = nextX + PLAYER_WIDTH - 1;
    int top = nextY;
    int bottom = nextY + PLAYER_HEIGHT - 1;

    // プレイヤーの左上と右上の当たり判定
    if (map->IsHit(left, top) || map->IsHit(right, top)) {
        return true;
    }
    // プレイヤーの左下と右下の当たり判定
    if (map->IsHit(left, bottom) || map->IsHit(right, bottom)) {
        return true;
    }

    return false; // 当たっていない場合
}
