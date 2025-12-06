#pragma once
#include <SDL3/SDL.h>

class Bullet
{
public:
    float x, y;
    float vx, vy;
    int w, h;
    SDL_Texture* texture;
    Bullet(float startX, float startY, float velX, float velY, int width, int height, SDL_Texture* tex);
    void update(float dt);
    void render(SDL_Renderer* renderer);
};

