#pragma once

// Librairie externe
#include <vector>
#include <iostream>

// Load SDL
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

// Forward declaration for Enemy class
class Enemy;

// CLass Bullet
class Bullet
{
public:

    // Variable for position/dimension
    float x, y;
    float h, w;

    // Variable for movement
    float vx, vy;

    // Variable for effect
    bool shouldExplode = false;

    // Variable for appearance
    SDL_Texture* bulletTexture = nullptr;

    // Constructor
    Bullet();
    Bullet(float startX, float startY, float velX, float velY, int width, int height);

    // Render/Update
    void renderBullets(SDL_Renderer* renderer, std::vector<Bullet>& bullets);
    void updateBullets(float dt, std::vector<Bullet>& bullets);
    // For bullet who explode, they launch lots of other balls flying in all directions
    void exploseBullet(int windowWidth, std::vector<Bullet>& bullets);
};