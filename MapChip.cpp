#include "MapChip.h"
#include "DxLib.h"

// コンストラクタでマップデータを初期化し、テクスチャを読み込む
MapChip::MapChip() {
    // サンプルのマップデータ（0:空、1:ブロック）
    map = {
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    // テクスチャを読み込む
    LoadTextures();
}

// デストラクタでテクスチャを解放する
MapChip::~MapChip() {
    UnloadTextures();
}

// テクスチャを読み込む
void MapChip::LoadTextures() {
    blockTexture = LoadGraph("block.png"); // ブロックのテクスチャ（1の値に対応）
    emptyTexture = LoadGraph("empty.png"); // 空のテクスチャ（0の値に対応）

    // テクスチャ読み込み失敗チェック
    if (blockTexture == -1 || emptyTexture == -1) {
        printfDx("テクスチャの読み込みに失敗しました。\n");
    }
}

// テクスチャを解放する
void MapChip::UnloadTextures() {
    DeleteGraph(blockTexture);
    DeleteGraph(emptyTexture);
}

// マップチップの描画
void MapChip::Draw() {
    for (int y = 0; y < map.size(); ++y) {
        for (int x = 0; x < map[y].size(); ++x) {
            int drawX = x * CHIP_SIZE;
            int drawY = y * CHIP_SIZE;

            if (map[y][x] == 1) {
                DrawGraph(drawX, drawY, blockTexture, TRUE); // ブロックテクスチャを描画
            }
            else {
                DrawGraph(drawX, drawY, emptyTexture, TRUE); // 空テクスチャを描画
            }
        }
    }
}

// 指定位置の当たり判定
bool MapChip::IsHit(int x, int y) {
    int mapX = x / CHIP_SIZE;
    int mapY = y / CHIP_SIZE;

    if (mapX < 0 || mapX >= MAP_WIDTH || mapY < 0 || mapY >= MAP_HEIGHT) {
        return true; // 範囲外は当たりとする
    }

    return map[mapY][mapX] == 1; // 1なら当たり判定
}
