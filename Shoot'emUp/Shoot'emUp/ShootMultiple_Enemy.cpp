#include "ShootMultiple_Enemy.h"


ShootMultiple_Enemy::ShootMultiple_Enemy()
{
    lastShotTime = 0;
    lastSpawnTime = 0;
}

ShootMultiple_Enemy::ShootMultiple_Enemy(float px, float py, float pw, float ph, float ps)
    : lastShotTime(0) {
}

void ShootMultiple_Enemy::spawnShootMultiple_Enemy(std::vector<ShootMultiple_Enemy>& triples, int windowWidth, int windowHeight) {
    ShootMultiple_Enemy t;
    t.w = 50;
    t.h = 50;
    t.x = windowWidth;
    t.y = randomInt(0, windowHeight - 50);
    t.color = { 0,0,255,255 };
    t.speed = 0.25;
    triples.emplace_back(t);

    // Santé
    int health = 3;
}


void ShootMultiple_Enemy::update(int windowWidth) {
    x -= speed; // x, y, speed viennent de Enemy !
}

void ShootMultiple_Enemy::shoot(std::vector<Bullet>& bullets, Uint32 now) 
{
    if (now - lastShotTime >= 1500) {
        float centerY = y + h / 2;

        // Tout droit - RALENTI
        bullets.emplace_back(x, centerY, -1, 0, 10, 5, color);

        // Vers le haut (20°) - RALENTI
        bullets.emplace_back(x, centerY, -1, -0.5, 10, 5, color);

        // Vers le bas (20°) - RALENTI
        bullets.emplace_back(x, centerY, -1, 0.5, 10, 5, color);

        lastShotTime = now;
    }
}

void ShootMultiple_Enemy::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // vert
    SDL_FRect rect = { x, y, w, h };
    SDL_RenderFillRect(renderer, &rect);
}