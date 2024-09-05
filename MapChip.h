#ifndef MAPCHIP_H
#define MAPCHIP_H

#include <vector>

class MapChip {
public:
    static const int CHIP_SIZE = 32;  // マップチップの1つのサイズ
    static const int MAP_WIDTH = 20;  // マップの横サイズ
    static const int MAP_HEIGHT = 15; // マップの縦サイズ

    MapChip();  // コンストラクタ
    ~MapChip(); // デストラクタ

    // マップチップの描画
    void Draw();

    // 指定位置の当たり判定
    bool IsHit(int x, int y);

private:
    std::vector<std::vector<int>> map;  // マップデータ
    int blockTexture; // ブロックのテクスチャ
    int emptyTexture; // 空のテクスチャ

    // テクスチャを読み込む
    void LoadTextures();
    // テクスチャを解放する
    void UnloadTextures();
};

#endif // MAPCHIP_H
