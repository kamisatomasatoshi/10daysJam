#ifndef PARTICLE_H
#define PARTICLE_H

#include "DxLib.h"
#include <vector>

// �p�[�e�B�N�����Ǘ�����N���X
class Particle {
public:
    Particle(float x, float y, float velX, float velY, int life);

    // �p�[�e�B�N���̍X�V
    void Update();

    // �p�[�e�B�N���̕`��
    void Draw() const;

    // �p�[�e�B�N�����������Ă��邩�ǂ����𔻒�
    bool IsAlive() const;

    // �p�[�e�B�N�����ꊇ��������֗��֐�
    static std::vector<Particle> CreateParticles(float x, float y, int count);

private:
    float posX, posY;   // �ʒu
    float velocityX, velocityY; // ���x
    int life = 40;  // ����
    int currentLife = 0;  // ���݂̌o�ߎ���
};

#endif
//main�ł̎g����
//while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
//    // �v���C���[�̈ړ�
//    if (CheckHitKey(KEY_INPUT_RIGHT)) playerX += 3;
//    if (CheckHitKey(KEY_INPUT_LEFT))  playerX -= 3;
//
//    // �p�[�e�B�N���𐶐��i�����Ƃ��Ɂj
//    if (CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_LEFT)) {
//        auto newParticles = Particle::CreateParticles(playerX, playerY + 16, 5);  // �v���C���[�̑����ɐ���
//        particles.insert(particles.end(), newParticles.begin(), newParticles.end());
//    }
//
//    // �p�[�e�B�N���̍X�V�ƕ`��
//    for (auto& particle : particles) {
//        particle.Update();
//        particle.Draw();
//    }
//
//    // �p�[�e�B�N���̎������s�������̂��폜
//    particles.erase(
//        std::remove_if(particles.begin(), particles.end(), [](const Particle& p) { return !p.IsAlive(); }),
//        particles.end()
//    );
//
//    // �v���C���[�̕`��
//    DrawBox(static_cast<int>(playerX - 16), static_cast<int>(playerY - 16), static_cast<int>(playerX + 16), static_cast<int>(playerY + 16), GetColor(255, 255, 255), TRUE);
//}