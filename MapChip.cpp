#include "MapChip.h"
#include "DxLib.h"

// コンストラクタでマップデータを初期化
MapChip::MapChip() {
    // サンプルのマップデータ（0:空、1:ブロック）
    map = {
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
}

// マップチップの描画
void MapChip::Draw() {
    for (int y = 0; y < map.size(); ++y) {
        for (int x = 0; x < map[y].size(); ++x) {
            if (map[y][x] == 1) {
                DrawBox(x * CHIP_SIZE, y * CHIP_SIZE, (x + 1) * CHIP_SIZE, (y + 1) * CHIP_SIZE, GetColor(255, 255, 255), TRUE);
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
