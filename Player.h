#ifndef PLAYER_H
#define PLAYER_H

#include "MapChip.h"

class Player {
public:
    static const int PLAYER_SIZE = MapChip::CHIP_SIZE;  // �v���C���[�̃T�C�Y�i32x32�j
    static const int MOVE_SPEED = 4;                    // �v���C���[�̈ړ����x
    static const int JUMP_POWER = -15;                  // �W�����v��
    static const int MAX_FALL_SPEED = 10;               // �ő嗎�����x
    static const int MAX_JUMPS = 3;                     // �󒆃W�����v�̍ő��
    static const int JUMP_COOLDOWN = 10;                // �W�����v�N�[���^�C���t���[��

    Player(int startX, int startY, MapChip* map);  // �R���X�g���N�^
    ~Player();  // �f�X�g���N�^

    // �v���C���[�̕`��
    void Draw();
    // �v���C���[�̍X�V�i�ړ��A�W�����v�A�����j
    void Update();

private:
    int x, y;             // �v���C���[�̈ʒu
    int vx, vy;           // �v���C���[�̑��x�ivx: �������x, vy: �������x�j
    int jumpsLeft;        // �c��W�����v��
    int jumpCooldown;     // �W�����v�N�[���^�C��
    bool isOnGround;      // �v���C���[���n�ʂɂ��邩�ǂ���
    int texture;          // �v���C���[�̃e�N�X�`��
    int playerFlag = true;
    MapChip* map;         // �}�b�v�ւ̃|�C���^�i�����蔻��Ɏg�p�j

    // �����蔻����`�F�b�N����
    bool CheckCollision(int nextX, int nextY);
    // �v���C���[�̉��ɒn�ʂ����邩���m�F����
    bool IsOnGround();
    // �e�N�X�`����ǂݍ���
    void LoadTexture();
    // �e�N�X�`�����������
    void UnloadTexture();
};

#endif // PLAYER_H
