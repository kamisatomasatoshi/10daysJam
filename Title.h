#pragma once
class Title
{
public:
	Title();	// コンストラクタ
	~Title();	// デストラクタ

	void Init();	// 初期化
	void Update();	// 更新
	void Draw();	// 描画
	void Reset();	// リセット

private:
	int x, y;
	int vx, vy;
	int texture;

	float time;

	void LoadTexture();
	void UnloadTexture();

};

