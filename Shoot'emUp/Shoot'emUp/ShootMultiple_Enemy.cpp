#include "ShootMultiple_Enemy.h"


Shooter_Enemy::Shooter_Enemy()
{
    lastShotTime = 0;
    lastSpawnTime = 0;
}

ShootMultiple_Enemy::ShootMultiple_Enemy(float px, float py, float pw, float ph, float ps)
    : lastShotTime(0) {
}

void ShootMultiple_Enemy::spawnShootMultipleEnemy(std::vector<ShootMultiple_Enemy>& triples, int windowWidth, int windowHeight) {
    triples.emplace_back(windowWidth, std::rand() % (windowHeight - 50), 50, 50, 2);
}



void ShootMultiple_Enemy::update(int windowWidth) {
    x -= speed; // x, y, speed viennent de Enemy !
}

void ShootMultiple_Enemy::shoot(std::vector<Bullet>& bullets, Uint32 now) {
    if (now - lastShotTime >= 1500) {
        float centerY = y + h / 2;

        // Tout droit - ordre : startX, startY, velX, velY, width, height, color
        bullets.emplace_back(x, centerY, -6, 0, 10, 5, color);

        // Vers le haut (45°)
        bullets.emplace_back(x, centerY, -6, -4, 10, 5, color);

        // Vers le bas (45°)
        bullets.emplace_back(x, centerY, -6, 4, 10, 5, color);

        lastShotTime = now;
    }
}

void ShootMultiple_Enemy::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // vert
    SDL_FRect rect = { x, y, w, h };
    SDL_RenderFillRect(renderer, &rect);
}