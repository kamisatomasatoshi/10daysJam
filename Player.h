#ifndef PLAYER_H
#define PLAYER_H

#include "MapChip.h"

class Player {
public:
    static const int PLAYER_WIDTH = MapChip::CHIP_SIZE;       // �v���C���[�̕�
    static const int PLAYER_HEIGHT = MapChip::CHIP_SIZE * 2;  // �v���C���[�̍����i�c��2�u���b�N���j
    static const int MOVE_SPEED = 4;                          // �v���C���[�̈ړ����x

    Player(int startX, int startY, MapChip* map);  // �R���X�g���N�^
    ~Player();  // �f�X�g���N�^

    // �v���C���[�̕`��
    void Draw();
    // �v���C���[�̍X�V�i�ړ��j
    void Update();

private:
    int x, y;         // �v���C���[�̈ʒu
    int texture;      // �v���C���[�̃e�N�X�`��
    MapChip* map;     // �}�b�v�ւ̃|�C���^�i�����蔻��Ɏg�p�j

    // �����蔻����`�F�b�N����
    bool CheckCollision(int nextX, int nextY);
    // �e�N�X�`����ǂݍ���
    void LoadTexture();
    // �e�N�X�`�����������
    void UnloadTexture();
};

#endif // PLAYER_H
