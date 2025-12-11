#pragma once
#include <vector>
#include "SDL3/SDL_render.h"

class Enemy
{
public:
    float x, y;
    float w, h;
    float speed;

    Enemy()
    {

    };
    Enemy(float _x, float _y, float _w, float _h, float _speed)
    {
        x = _x;
        y = _y;
        w = _w;
        h = _h;
        speed = _speed;
    };
};
void updateEnemies(std::vector<Enemy>& enemies);
void renderEnemies(SDL_Renderer* renderer, const std::vector<Enemy>& enemies);
void spawnEnemy(std::vector<Enemy>& enemies, int windowWidth, int windowHeight);
