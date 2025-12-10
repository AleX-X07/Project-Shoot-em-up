#include "ShootMultiple_Enemy.h"



void ShootMultiple_Enemy::spawnShootMultipleEnemy(std::vector<ShootMultiple_Enemy>& triples, int windowWidth, int windowHeight) {
    triples.emplace_back(windowWidth, std::rand() % (windowHeight - 50), 50, 50, 2);
}

ShootMultiple_Enemy::ShootMultiple_Enemy(float px, float py, float pw, float ph, float ps)
    : Enemy(px, py, pw, ph, ps), lastShotTime(0) {
}

void ShootMultiple_Enemy::update(int windowWidth) {
    x -= speed; // x, y, speed viennent de Enemy !
}

void ShootMultiple_Enemy::shoot(std::vector<Projectile>& projectiles, Uint32 now) {
    if (now - lastShotTime >= 1000) {
        float centerY = y + h / 2;

        // Tout droit
        projectiles.push_back({ x, centerY, 10, 5, -6, 0 });
        // Vers le haut (45°)
        projectiles.push_back({ x, centerY, 10, 5, -6, -4 });
        // Vers le bas (45°)
        projectiles.push_back({ x, centerY, 10, 5, -6, 4 });

        lastShotTime = now;
    }
}

void ShootMultiple_Enemy::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // vert
    SDL_FRect rect = { x, y, w, h };
    SDL_RenderFillRect(renderer, &rect);
}