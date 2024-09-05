#include "Player.h"
#include "DxLib.h"

// �R���X�g���N�^
Player::Player(int startX, int startY, MapChip* map)
    : x(startX), y(startY), map(map) {
    LoadTexture(); // �v���C���[�̃e�N�X�`����ǂݍ���
}

// �f�X�g���N�^
Player::~Player() {
    UnloadTexture(); // �v���C���[�̃e�N�X�`�������
}

// �e�N�X�`����ǂݍ���
void Player::LoadTexture() {
    texture = LoadGraph("player.png"); // �v���C���[�̃e�N�X�`��
    if (texture == -1) {
        printfDx("�v���C���[�̃e�N�X�`���̓ǂݍ��݂Ɏ��s���܂����B\n");
    }
}

// �e�N�X�`�����������
void Player::UnloadTexture() {
    DeleteGraph(texture);
}

// �v���C���[�̕`��
void Player::Draw() {
    DrawGraph(x, y, texture, TRUE);
}

// �v���C���[�̍X�V�i�ړ��j
void Player::Update() {
    int nextX = x, nextY = y;

    // W: ��Ɉړ�
    if (CheckHitKey(KEY_INPUT_W)) {
        nextY -= MOVE_SPEED;
    }
    // A: ���Ɉړ�
    if (CheckHitKey(KEY_INPUT_A)) {
        nextX -= MOVE_SPEED;
    }
    // S: ���Ɉړ�
    if (CheckHitKey(KEY_INPUT_S)) {
        nextY += MOVE_SPEED;
    }
    // D: �E�Ɉړ�
    if (CheckHitKey(KEY_INPUT_D)) {
        nextX += MOVE_SPEED;
    }

    // �����蔻����`�F�b�N
    if (!CheckCollision(nextX, nextY)) {
        x = nextX;
        y = nextY;
    }
}

// �����蔻����`�F�b�N����
bool Player::CheckCollision(int nextX, int nextY) {
    // �v���C���[��4�����`�F�b�N
    int left = nextX;
    int right = nextX + PLAYER_WIDTH - 1;
    int top = nextY;
    int bottom = nextY + PLAYER_HEIGHT - 1;

    // �v���C���[�̍���ƉE��̓����蔻��
    if (map->IsHit(left, top) || map->IsHit(right, top)) {
        return true;
    }
    // �v���C���[�̍����ƉE���̓����蔻��
    if (map->IsHit(left, bottom) || map->IsHit(right, bottom)) {
        return true;
    }

    return false; // �������Ă��Ȃ��ꍇ
}
