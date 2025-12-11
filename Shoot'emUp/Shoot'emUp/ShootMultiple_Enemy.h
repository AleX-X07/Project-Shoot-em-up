#pragma once
#include "Classic_enemy.h"
#include "Enemy.h"

class ShootMultiple_Enemy : public Enemy {
public:
    Uint32 lastShotTime;

    ShootMultiple_Enemy(float px, float py, float pw, float ph, float ps);
    void update(int windowWidth);
    void shoot(std::vector<Projectile>& projectiles, Uint32 now);
    void render(SDL_Renderer* renderer);
    static void spawnShootMultipleEnemy(std::vector<ShootMultiple_Enemy>& triples, int windowWidth, int windowHeight);
};

