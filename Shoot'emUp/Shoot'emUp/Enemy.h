#pragma once
#include <vector>
#include "SDL3/SDL_render.h"

class Enemy
{
public:
    int x, y;
    int w, h;
    int speed;

    Enemy()
    {

    };
    Enemy(int _x, int _y, int _w, int _h, int _speed)
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
