#ifndef PLAYER_H
#define PLAYER_H

#include "MapChip.h"
#include "Particle.h"
class Player {
public:
	static const int PLAYER_SIZE = MapChip::CHIP_SIZE;  // プレイヤーのサイズ（32x32）
	static const int MOVE_SPEED = 4;                    // プレイヤーの移動速度
	static const int JUMP_POWER = -15;                  // ジャンプ力
	static const int MAX_FALL_SPEED = 30;               // 最大落下速度
	static const int MAX_JUMPS = 3;                     // 空中ジャンプの最大回数
	static const int JUMP_COOLDOWN = 10;                // ジャンプクールタイムフレーム
	bool gualFlag = false;
	bool playerFlag = true;
	int scrollY = 0;

	

	Player(int startX, int startY, MapChip* map);  // コンストラクタ
	~Player();  // デストラクタ

	// プレイヤーの描画
	void Draw();
	// プレイヤーの更新（移動、ジャンプ、落下）
	void Update(int win_hei);
	// リセット関数
	void Reset();

	public :
	int x, y;             // プレイヤーの位置
	int vx, vy;           // プレイヤーの速度（vx: 水平速度, vy: 垂直速度）
	int jumpsLeft;        // 残りジャンプ回数
	int jumpCooldown;     // ジャンプクールタイム
	bool isOnGround;      // プレイヤーが地面にいるかどうか
	bool isOnGaul;		  // プレイヤーがゴールにいるかどうか
	int texture;          // プレイヤーのテクスチャ
	// リセット用変数
	int Rx, Ry;
	int Rvx, Rvy;
	int RisJump, RjumpCoolDown;
	int RisOnGround;
	int Rmap;
	int RscrollY;
	// 移動しているかどうかのフラグ( 0:停止中  1:移動中 )
	int Move = 0;
	// 移動し始めてから何フレーム経過したかを保持する変数
	int MoveCounter;
	MapChip* map;         // マップへのポインタ（当たり判定に使用）

	// 当たり判定をチェックする
	bool CheckCollision(int nextX, int nextY);
	// プレイヤーの下に地面があるかを確認する
	bool IsOnGround();
	// プレイヤーの下に地面があるかを確認する
	bool IsOnGaul();
	// テクスチャを読み込む
	void LoadTexture();
	// テクスチャを解放する
	void UnloadTexture();
};

#endif // PLAYER_H
