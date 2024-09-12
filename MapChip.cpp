#include "MapChip.h"

// コンストラクタでマップデータを初期化し、テクスチャを読み込む
MapChip::MapChip() {

	// テクスチャを読み込む
	LoadTextures();

	// 描画用の初期値設定
	MapDrawPointX = 0;
	MapDrawPointY = 0;
}

// デストラクタでテクスチャを解放する
MapChip::~MapChip() {
	UnloadTextures();
}

void MapChip::SetMapNo(int MapNo_)
{
	if (MapNo < 0 || MapNo >= MAP_NUM) {
		printfDx("エラー: 不正なマップ番号 %d が指定されました。\n", MapNo);
		return;
	}
	MapNo = MapNo_;
}

// テクスチャを読み込む
void MapChip::LoadTextures() {
	emptyTexture = LoadGraph("Resource/emptyTexture.png"); // 空のテクスチャ（0の値に対応）
	blockTexture = LoadGraph("Resource/Block01.png"); // ブロックのテクスチャ（1の値に対応）
	goalTexture = LoadGraph("Resource/blockTexture.png"); // ブロックのテクスチャ（1の値に対応）

	// テクスチャ読み込み失敗チェック
	if (blockTexture == -1 || emptyTexture == -1) {
		printfDx("テクスチャの読み込みに失敗しました。\n");
	}
}

// テクスチャを解放する
void MapChip::UnloadTextures() {
	DeleteGraph(blockTexture);
	DeleteGraph(emptyTexture);
	DeleteGraph(goalTexture);
}

// マップチップの描画
void MapChip::Draw(int ScrollY) {
	if (MapNo < 0 || MapNo >= MAP_NUM) {
		printfDx("エラー: 無効なマップ番号 %d が指定されています。\n", MapNo);
		return;
	}

	int j, i;

	// 描画するマップチップの数をセット
	DrawMapChipNumX = 100;
	DrawMapChipNumY = 1000;

	// 画面左上に描画するマップ座標をセット
	MapDrawPointX = 0;
	MapDrawPointY = 0;

	// マップを描く
	for (i = 0; i < DrawMapChipNumY; i++) {
		for (j = 0; j < DrawMapChipNumX; j++) {
			if ((j + MapDrawPointX < 0) || (i + MapDrawPointY < 0) ||
				(j + MapDrawPointX >= MapData[MapNo].Width) || (i + MapDrawPointY >= MapData[MapNo].Height)) {
				continue;
			}

			// マップデータが0だったら空テクスチャを描画
			if (MapData[MapNo].Data[i + MapDrawPointY][j + MapDrawPointX] == 0) {
				DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE - ScrollY, emptyTexture, TRUE);
			}
			// マップデータが1だったらブロックテクスチャを描画
			else if (MapData[MapNo].Data[i + MapDrawPointY][j + MapDrawPointX] == 1) {
				DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE - ScrollY, blockTexture, TRUE);
			}
			// マップデータが1だったらブロックテクスチャを描画
			else if (MapData[MapNo].Data[i + MapDrawPointY][j + MapDrawPointX] == 2) {
				DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE - ScrollY, goalTexture, TRUE);
			}
		}
	}
}

// 指定位置の当たり判定
bool MapChip::IsHit(int x, int y) {
	int mapX = x / CHIP_SIZE;
	int mapY = y / CHIP_SIZE;

	// 範囲外を当たりとする
	if (mapX < 0 || mapX >= MAP_WIDTH || mapY < 0 || mapY >= MAP_HEIGHT) {
		return true;
	}

	// マップデータが1なら当たり判定
	return MapData[MapNo].Data[mapY][mapX] == 1;
}

bool MapChip::IsGual(int x, int y) {
	int mapX = x / CHIP_SIZE;
	int mapY = y / CHIP_SIZE;

	// 範囲外を当たりとする
	if (mapX < 0 || mapX >= MAP_WIDTH || mapY < 0 || mapY >= MAP_HEIGHT) {
		return true;
	}

	// マップデータが2なら当たり判定
	return MapData[MapNo].Data[mapY][mapX] == 2;
}
