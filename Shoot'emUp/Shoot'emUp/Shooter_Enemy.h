#pragma once
#include <vector>
#include <SDL3/SDL.h>
#include "Enemy.h"
#include "Bullet.h"
class Shooter_Enemy : public Enemy {
public:
    Uint32 lastShotTime;

    Uint32 lastSpawnTime = 0;
    Uint32 now = SDL_GetTicks();
    Shooter_Enemy();
    Shooter_Enemy(float px, float py, float pw, float ph, float ps, int health, SDL_Color color);

    void update(int windowWidth) override;
    void shoot(std::vector<Bullet>& bullets, Uint32 now);
    void render(SDL_Renderer* renderer) override;
    static void spawnShooter_Enemy(std::vector<Shooter_Enemy>& Shooter, int windowWidth, int windowHeight);
    static void updateShooter_Enemy(std::vector<Shooter_Enemy>& Shooter);
};
