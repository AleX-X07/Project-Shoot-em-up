#pragma once
#include <SDL3/SDL.h>

class Bullet
{
public:
    float x, y;
    float vx, vy;
    int w, h;

    Bullet() = default;

    SDL_Texture* texture = nullptr;  
    SDL_Color color;
    Bullet(float startX, float startY, float velX, float velY, int width, int height, SDL_Color col);
    void update(float dt);
    void render(SDL_Renderer* renderer);
};