#ifndef PARTICLE_H
#define PARTICLE_H

#include "DxLib.h"
#include <vector>

// パーティクルを管理するクラス
class Particle {
public:
    Particle(float x, float y, float velX, float velY, int life);

    // パーティクルの更新
    void Update();

    // パーティクルの描画
    void Draw() const;

    // パーティクルが生存しているかどうかを判定
    bool IsAlive() const;

    // パーティクルを一括生成する便利関数
    static std::vector<Particle> CreateParticles(float x, float y, int count);

private:
    float posX, posY;   // 位置
    float velocityX, velocityY; // 速度
    int life = 40;  // 寿命
    int currentLife = 0;  // 現在の経過時間
};

#endif
//mainでの使い方
//while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
//    // プレイヤーの移動
//    if (CheckHitKey(KEY_INPUT_RIGHT)) playerX += 3;
//    if (CheckHitKey(KEY_INPUT_LEFT))  playerX -= 3;
//
//    // パーティクルを生成（歩くときに）
//    if (CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_LEFT)) {
//        auto newParticles = Particle::CreateParticles(playerX, playerY + 16, 5);  // プレイヤーの足元に生成
//        particles.insert(particles.end(), newParticles.begin(), newParticles.end());
//    }
//
//    // パーティクルの更新と描画
//    for (auto& particle : particles) {
//        particle.Update();
//        particle.Draw();
//    }
//
//    // パーティクルの寿命が尽きたものを削除
//    particles.erase(
//        std::remove_if(particles.begin(), particles.end(), [](const Particle& p) { return !p.IsAlive(); }),
//        particles.end()
//    );
//
//    // プレイヤーの描画
//    DrawBox(static_cast<int>(playerX - 16), static_cast<int>(playerY - 16), static_cast<int>(playerX + 16), static_cast<int>(playerY + 16), GetColor(255, 255, 255), TRUE);
//}