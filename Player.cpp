#include "Player.h"
#include "DxLib.h"

// �R���X�g���N�^
Player::Player(int startX, int startY, MapChip* map)
    : x(startX), y(startY), vx(0), vy(0), jumpsLeft(MAX_JUMPS), jumpCooldown(0), isOnGround(false), map(map) {
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

// �v���C���[�̍X�V�i�ړ��A�W�����v�A�����j
void Player::Update() {
    int nextX = x, nextY = y;

    // ���������̈ړ�
    if (CheckHitKey(KEY_INPUT_A)) {
        nextX -= MOVE_SPEED;
    }
    if (CheckHitKey(KEY_INPUT_D)) {
        nextX += MOVE_SPEED;
    }

    // �W�����v�iW�L�[�j
    if (CheckHitKey(KEY_INPUT_W) && jumpsLeft > 0 && jumpCooldown == 0) {
        vy = JUMP_POWER;  // �W�����v�͂�^����
        jumpsLeft--;      // �W�����v�񐔂����炷
        jumpCooldown = JUMP_COOLDOWN;  // �N�[���^�C�������Z�b�g
    }

    // �N�[���^�C���̏���
    if (jumpCooldown > 0) {
        jumpCooldown--;
    }

    // �d�͂ɂ�闎��
    if (!isOnGround) {
        vy++;  // �d�͂ŉ���
        if (vy > MAX_FALL_SPEED) {
            vy = MAX_FALL_SPEED;  // �ő嗎�����x�𐧌�
        }
    }

    // ���������̈ړ�
    nextY += vy;

    // �����蔻����`�F�b�N
    if (!CheckCollision(nextX, nextY)) {
        x = nextX;
        y = nextY;
    }
    else {
        // �n�ʂƂ̏Փˎ��ɐ������x�����Z�b�g
        if (vy > 0) {
            vy = 0;
        }
    }

    // �v���C���[���n�ʂɂ��邩�ǂ����m�F
    isOnGround = IsOnGround();
    if (isOnGround) {
        jumpsLeft = MAX_JUMPS;  // �n�ʂɂ���Ȃ�W�����v�񐔂����Z�b�g
    }
}

// �����蔻����`�F�b�N����
bool Player::CheckCollision(int nextX, int nextY) {
    // �v���C���[��4�����`�F�b�N
    int left = nextX;
    int right = nextX + PLAYER_SIZE - 1;
    int top = nextY;
    int bottom = nextY + PLAYER_SIZE - 1;

    // ����A�E��A�����A�E���̓����蔻��
    if (map->IsHit(left, top) || map->IsHit(right, top) || map->IsHit(left, bottom) || map->IsHit(right, bottom)) {
        return true;
    }

    return false;  // �������Ă��Ȃ��ꍇ
}

// �v���C���[�̉��ɒn�ʂ����邩���m�F����
bool Player::IsOnGround() {
    int left = x;
    int right = x + PLAYER_SIZE - 1;
    int bottom = y + PLAYER_SIZE;  // �v���C���[�̉�����1�s�N�Z�������`�F�b�N

    // �����ƉE���̉��Ƀu���b�N������Βn�ʂɂ���Ɣ���
    return map->IsHit(left, bottom) || map->IsHit(right, bottom);
}
