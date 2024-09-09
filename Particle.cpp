#include "Particle.h"

// �R���X�g���N�^
Particle::Particle(float x, float y, float velX, float velY, int life)
    : posX(x), posY(y), velocityX(velX), velocityY(velY), life(life), currentLife(0) {
}

// �p�[�e�B�N���̍X�V����
void Particle::Update() {
    // �p�[�e�B�N���̈ʒu���X�V
    posX += velocityX;
    posY += velocityY;

    // �d�͂�������i���������˂�悤�ȉ��o�����邽�߁j
    velocityY += 0.1f;

    // �����̌o��
    currentLife++;
}

// �p�[�e�B�N���̕`�揈��
void Particle::Draw() const {
    if (IsAlive()) {
        // �p�[�e�B�N���̐F��T�C�Y�Ȃǂ͓K�X����
        DrawCircle(static_cast<int>(posX), static_cast<int>(posY), 2, GetColor(255, 255, 255), TRUE);
    }
}

// �p�[�e�B�N�����܂������Ă��邩�i�������c���Ă��邩�j�𔻒�
bool Particle::IsAlive() const {
    return currentLife < life;
}

// �����̃p�[�e�B�N���𐶐�����֐�
std::vector<Particle> Particle::CreateParticles(float x, float y, int count) {
    std::vector<Particle> particles;
    for (int i = 0; i < count; i++) {
        // �����_���ȕ����ɔ�ԃp�[�e�B�N�����쐬
        float velX = (rand() % 100 - 50) / 100.0f;  // -0.5 ���� 0.5 �̊Ԃ̑��x
        float velY = (rand() % 100 - 50) / 100.0f;  // -0.5 ���� 0.5 �̊Ԃ̑��x
        particles.push_back(Particle(x, y, velX, velY, 60));  // ����60�t���[��
    }
    return particles;
}
