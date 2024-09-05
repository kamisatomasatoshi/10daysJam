#include "MapChip.h"
#include "DxLib.h"

// �R���X�g���N�^�Ń}�b�v�f�[�^��������
MapChip::MapChip() {
    // �T���v���̃}�b�v�f�[�^�i0:��A1:�u���b�N�j
    map = {
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
}

// �}�b�v�`�b�v�̕`��
void MapChip::Draw() {
    for (int y = 0; y < map.size(); ++y) {
        for (int x = 0; x < map[y].size(); ++x) {
            if (map[y][x] == 1) {
                DrawBox(x * CHIP_SIZE, y * CHIP_SIZE, (x + 1) * CHIP_SIZE, (y + 1) * CHIP_SIZE, GetColor(255, 255, 255), TRUE);
            }
        }
    }
}

// �w��ʒu�̓����蔻��
bool MapChip::IsHit(int x, int y) {
    int mapX = x / CHIP_SIZE;
    int mapY = y / CHIP_SIZE;

    if (mapX < 0 || mapX >= MAP_WIDTH || mapY < 0 || mapY >= MAP_HEIGHT) {
        return true; // �͈͊O�͓�����Ƃ���
    }

    return map[mapY][mapX] == 1; // 1�Ȃ瓖���蔻��
}
