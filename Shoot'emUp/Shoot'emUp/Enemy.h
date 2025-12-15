#pragma once
#include <vector>
#include <random>
#include "SDL3/SDL.h"

class Enemy
{
public:
    float x, y;
    float w, h;
    float speed;
    SDL_FRect rect;
    SDL_Texture* texture;
    SDL_Color color;

    Enemy();
    Enemy(float _x, float _y, float _w, float _h, float _speed, SDL_Color color);
    static int randomInt(int min, int max);
    static void updateEnemy(std::vector<Enemy>& enemies);
    static void renderEnemy(SDL_Renderer* renderer, const std::vector<Enemy>& enemies);
    static void spawnEnemy(std::vector<Enemy>& enemies, int windowWidth, int windowHeight);
    /*void Collide(std::vector<Enemy>& enemies);*/
};