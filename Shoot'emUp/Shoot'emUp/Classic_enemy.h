#pragma once
#include "Enemy.h"
#include <vector>
#include <SDL3/SDL.h>

struct Projectile {
    float x, y;
    float w, h;
    float speed;
};

class Classic_enemy : private Enemy
{
public:
    float x, y;
    float w, h;
    float speed;
    Uint32 lastShotTime;

    Classic_enemy(float px, float py, float pw, float ph, float ps)
        : x(px), y(py), w(pw), h(ph), speed(ps), lastShotTime(0) {
    }

    void shoot(std::vector<Projectile>& projectiles, Uint32 now) {
        if (now - lastShotTime >= 500) { // 0.5s
            Projectile p;
            p.x = x;
            p.y = y + h / 2;
            p.w = 10;
            p.h = 5;
            p.speed = speed * 2;
            projectiles.push_back(p);
            lastShotTime = now;
        }
    }
};