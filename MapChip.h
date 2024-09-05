#ifndef MAPCHIP_H
#define MAPCHIP_H

#include <vector>

class MapChip {
public:
    static const int CHIP_SIZE = 32;  // �}�b�v�`�b�v��1�̃T�C�Y
    static const int MAP_WIDTH = 20;  // �}�b�v�̉��T�C�Y
    static const int MAP_HEIGHT = 15; // �}�b�v�̏c�T�C�Y

    MapChip();  // �R���X�g���N�^

    // �}�b�v�`�b�v�̕`��
    void Draw();

    // �w��ʒu�̓����蔻��
    bool IsHit(int x, int y);

private:
    std::vector<std::vector<int>> map;  // �}�b�v�f�[�^
};

#endif // MAPCHIP_H