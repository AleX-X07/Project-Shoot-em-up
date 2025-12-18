#pragma once
#include <vector>
#include <random>
#include "SDL3/SDL.h"
#include "Hero.h"

class Enemy
{
public:
    float x, y;
    float w, h;
    float speed;
    SDL_FRect rect;
    SDL_Texture* enemyTexture;
    std::vector<Enemy>enemies;
    SDL_Color color;
    int HP;
    int Value;

    Enemy();
    Enemy(float _x, float _y, float _w, float _h, float _speed, SDL_Color color);
    static int randomInt(int min, int max);
    static void updateEnemy(std::vector<Enemy>& enemies);
    static void renderEnemy(SDL_Renderer* renderer, const std::vector<Enemy>& enemies);
    static void spawnEnemy(std::vector<Enemy>& enemies, int windowWidth, int windowHeight, SDL_Renderer* renderer, SDL_Texture* sharedTexture);

    ~Enemy();
};