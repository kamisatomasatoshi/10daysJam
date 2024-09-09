#pragma once

#include "DxLib.h"

#define MAP_NUM 5 // マップ数
#define MAP_WIDTH  40 // マップの横サイズ
#define MAP_HEIGHT 40 // マップの縦サイズ

class MapChip {
public:
	static const int CHIP_SIZE = 32; // マップチップの1つのサイズ

	MapChip();  // コンストラクタ
	~MapChip(); // デストラクタ

	// マップチップの描画
	void Draw();

	// 指定位置の当たり判定
	bool IsHit(int x, int y);

	int GetMapNo() { return MapNo; }
	void SetMapNo(int MapNo_);

private:
	int blockTexture; // ブロックのテクスチャ
	int emptyTexture; // 空のテクスチャ
	int MapNo = 0; // 現在のマップ番号
	int MapDrawPointX, MapDrawPointY;     // 描画するマップ座標値
	int DrawMapChipNumX, DrawMapChipNumY; // 描画するマップチップの数

	// テクスチャを読み込む
	void LoadTextures();
	// テクスチャを解放する
	void UnloadTextures();

	// マップの構造体
	struct MAPDATA {
		int Width;  // マップの幅
		int Height; // マップの高さ
		int Data[MAP_HEIGHT][MAP_WIDTH]; // マップのデータ（0:空、1:ブロック）
	};

	MAPDATA MapData[MAP_NUM] = {
		// サンプルのマップデータ
		{
			10, 20,
			{
				{1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
				{1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
				{1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
				{1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
				{1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
				{1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
				{1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
				{1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
				{1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
				{1, 1, 1, 1, 1, 1, 0, 0, 1, 1},
				{1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
				{1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
				{1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
				{1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
				{1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
				{1, 1, 0, 0, 0, 1, 1, 1, 1, 1},
				{1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
				{1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
				{1, 1, 1, 1, 1, 1, 0, 0, 1, 1},
			}
		},
	};
};