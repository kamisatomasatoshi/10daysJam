#include "Particle.h"

// コンストラクタ
Particle::Particle(float x, float y, float velX, float velY, int life)
    : posX(x), posY(y), velocityX(velX), velocityY(velY), life(life), currentLife(0) {
}

// パーティクルの更新処理
void Particle::Update() {
    // パーティクルの位置を更新
    posX += velocityX;
    posY += velocityY;

    // 重力を加える（砂利が跳ねるような演出をするため）
    velocityY += 0.1f;

    // 寿命の経過
    currentLife++;
}

// パーティクルの描画処理
void Particle::Draw() const {
    if (IsAlive()) {
        // パーティクルの色やサイズなどは適宜調整
        DrawCircle(static_cast<int>(posX), static_cast<int>(posY), 2, GetColor(255, 255, 255), TRUE);
    }
}

// パーティクルがまだ生きているか（寿命が残っているか）を判定
bool Particle::IsAlive() const {
    return currentLife < life;
}

// 複数のパーティクルを生成する関数
std::vector<Particle> Particle::CreateParticles(float x, float y, int count) {
    std::vector<Particle> particles;
    for (int i = 0; i < count; i++) {
        // ランダムな方向に飛ぶパーティクルを作成
        float velX = (rand() % 100 - 50) / 100.0f;  // -0.5 から 0.5 の間の速度
        float velY = (rand() % 100 - 50) / 100.0f;  // -0.5 から 0.5 の間の速度
        particles.push_back(Particle(x, y, velX, velY, 60));  // 寿命60フレーム
    }
    return particles;
}
