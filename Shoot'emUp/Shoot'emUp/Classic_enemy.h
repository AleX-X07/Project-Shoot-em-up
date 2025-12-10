#pragma once
#include <vector>
#include <SDL3/SDL.h>
#include "Enemy.h"

struct Projectile {
    float x, y;
    float w, h;
    float speed;
    float speedY = 0;
};

class Classic_enemy : public Enemy {
public:
    Uint32 lastShotTime;

    Classic_enemy(float px, float py, float pw, float ph, float ps);

    void update(int windowWidth);
    void shoot(std::vector<Projectile>& projectiles, Uint32 now);
    void render(SDL_Renderer* renderer);
    static void spawnClassicEnemy(std::vector<Classic_enemy>& classics, int windowWidth, int windowHeight);
};
