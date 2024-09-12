#include "Player.h"
#include "DxLib.h"

// コンストラクタ
Player::Player(int startX, int startY, MapChip* map)
 :x(startX), y(startY), vx(0), vy(0), jumpsLeft(MAX_JUMPS), jumpCooldown(0), isOnGround(false), map(map) {
    LoadTexture(); // プレイヤーのテクスチャを読み込む

}

// デストラクタ
Player::~Player() {


    UnloadTexture(); // プレイヤーのテクスチャを解放

}

// テクスチャを読み込む
void Player::LoadTexture() {

	
    texture = LoadGraph("slime.png"); // プレイヤーのテクスチャ

    if (texture == -1) {
        printfDx("プレイヤーのテクスチャの読み込みに失敗しました。\n");
    };

}

// テクスチャを解放する
void Player::UnloadTexture() {
	DeleteGraph(texture);
}

// プレイヤーの描画
void Player::Draw() {
	if (playerFlag == true) {
		DrawGraph(x, y, texture, TRUE);
	}

	DrawFormatString(512, 0, GetColor(255, 255, 255), "�d��%d", vy);
	DrawFormatString(512, 16, GetColor(255, 255, 255), "�t���O%d", playerFlag);
	DrawFormatString(512, 32, GetColor(255, 255, 255), "%d", isOnGround);
}

// プレイヤーの更新（移動、ジャンプ、落下）
void Player::Update() {
  
    int nextX = x, nextY = y;

    // 水平方向の移動
    if (CheckHitKey(KEY_INPUT_A)) {
        nextX -= MOVE_SPEED;
    }
    if (CheckHitKey(KEY_INPUT_D)) {
        nextX += MOVE_SPEED;
    }

    // ジャンプ（Wキー）
    if (CheckHitKey(KEY_INPUT_W) && jumpsLeft > 0 && jumpCooldown == 0) {
        vy = JUMP_POWER;  // ジャンプ力を与える
        jumpsLeft--;      // ジャンプ回数を減らす
        jumpCooldown = JUMP_COOLDOWN;  // クールタイムをリセット
    }

    // クールタイムの処理
    if (jumpCooldown > 0) {
        jumpCooldown--;
    }

    // 重力による落下
    if (!isOnGround) {
        vy++;  // 重力で加速
        if (vy > MAX_FALL_SPEED) {
            vy = MAX_FALL_SPEED;  // 最大落下速度を制限
        }
    }

    // 垂直方向の移動
    nextY += vy;

    // 当たり判定をチェック
    if (!CheckCollision(nextX, nextY)) {
        x = nextX;
        y = nextY;
    }
    else {
        // 地面との衝突時に垂直速度をリセット
        if (vy > 0) {
            vy = 0;
        }
    }

    // プレイヤーが地面にいるかどうか確認
    isOnGround = IsOnGround();
    if (isOnGround) {
        jumpsLeft = MAX_JUMPS;  // 地面にいるならジャンプ回数をリセット
    }

}

// 当たり判定をチェックする
bool Player::CheckCollision(int nextX, int nextY) {

    // プレイヤーの4隅をチェック
    int left = nextX;
    int right = nextX + PLAYER_SIZE - 1;
    int top = nextY;
    int bottom = nextY + PLAYER_SIZE - 1;

    // 左上、右上、左下、右下の当たり判定
    if (map->IsHit(left, top) || map->IsHit(right, top) || map->IsHit(left, bottom) || map->IsHit(right, bottom)) {
        return true;
    }

    return false;  // 当たっていない場合

}

// プレイヤーの下に地面があるかを確認する
bool Player::IsOnGround() {
    int left = x;
    int right = x + PLAYER_SIZE - 1;
    int bottom = y + PLAYER_SIZE;  // プレイヤーの下部の1ピクセル下をチェック

    // 左下と右下の下にブロックがあれば地面にいると判定
    return map->IsHit(left, bottom) || map->IsHit(right, bottom);

}
