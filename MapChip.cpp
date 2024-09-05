#include "MapChip.h"
#include "DxLib.h"

// �R���X�g���N�^�Ń}�b�v�f�[�^�����������A�e�N�X�`����ǂݍ���
MapChip::MapChip() {
    // �T���v���̃}�b�v�f�[�^�i0:��A1:�u���b�N�j
    map = {
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    // �e�N�X�`����ǂݍ���
    LoadTextures();
}

// �f�X�g���N�^�Ńe�N�X�`�����������
MapChip::~MapChip() {
    UnloadTextures();
}

// �e�N�X�`����ǂݍ���
void MapChip::LoadTextures() {
    blockTexture = LoadGraph("block.png"); // �u���b�N�̃e�N�X�`���i1�̒l�ɑΉ��j
    emptyTexture = LoadGraph("empty.png"); // ��̃e�N�X�`���i0�̒l�ɑΉ��j

    // �e�N�X�`���ǂݍ��ݎ��s�`�F�b�N
    if (blockTexture == -1 || emptyTexture == -1) {
        printfDx("�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂����B\n");
    }
}

// �e�N�X�`�����������
void MapChip::UnloadTextures() {
    DeleteGraph(blockTexture);
    DeleteGraph(emptyTexture);
}

// �}�b�v�`�b�v�̕`��
void MapChip::Draw() {
    for (int y = 0; y < map.size(); ++y) {
        for (int x = 0; x < map[y].size(); ++x) {
            int drawX = x * CHIP_SIZE;
            int drawY = y * CHIP_SIZE;

            if (map[y][x] == 1) {
                DrawGraph(drawX, drawY, blockTexture, TRUE); // �u���b�N�e�N�X�`����`��
            }
            else {
                DrawGraph(drawX, drawY, emptyTexture, TRUE); // ��e�N�X�`����`��
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
