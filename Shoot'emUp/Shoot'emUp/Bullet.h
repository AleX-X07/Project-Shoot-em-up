#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>
#include <iostream>

class Enemy;

class Bullet
{
public:
    float x, y;
    float vx, vy;
    float h, w;
    int _vx, _vy;
    bool shouldExplose = false;
    SDL_Color color;
    SDL_Texture* bulletTexture = nullptr;

    Uint32 now = SDL_GetTicks();
    Uint32 lastShotTime = 0;

    std::vector<Bullet> exploseBulletVector;
    Bullet();
    Bullet(float startX, float startY, float velX, float velY, int width, int height, SDL_Color col);
    void renderBullets(SDL_Renderer* renderer, std::vector<Bullet>& bullets);
    void updateBullets(float dt, std::vector<Bullet>& bullets);
    void exploseBullet(int windowWidth, std::vector<Bullet>& bullets);
};