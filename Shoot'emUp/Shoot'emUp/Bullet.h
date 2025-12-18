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
    SDL_Color color;
    SDL_Texture* bulletTexture = nullptr;
    std::vector<Bullet> bullets;
    Bullet();
    Bullet(float startX, float startY, float velX, float velY, int width, int height, SDL_Color col);
    void renderBullets(SDL_Renderer* renderer);
    void updateBullets(float dt);
    void loadBulletTexture(SDL_Renderer* renderer, const char* filepath);
    void BulletCollide(std::vector<Bullet>& bullets, std::vector<Enemy>& enemies);
};