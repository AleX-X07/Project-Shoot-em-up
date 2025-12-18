#pragma once
#include <iostream>
#include <SDL3/SDL.h>
#include <vector>
#include <SDL3_image/SDL_image.h>
#include "Bullet.h"

class Enemy;

class Entity : public Bullet { // Class for player
public:

    SDL_FRect rect;
    SDL_Texture* texture;
    SDL_Color color;
    float speed;
    float shootCooldown = 0.15f;      
    float timeSinceLastShot = 0.0f;
	int HP = 4;
    int Score = 0;

    Entity();
    Entity(float x, float y, float w, float h, SDL_Texture* tex, float spd = 200.0f);
    Entity(float x, float y, float w, float h, SDL_Color col, float spd = 200.0f);

    void move(float dx, float dy, float dt); // Function for move player
    void clampToScreen(int screenWidth, int screenHeight); // Function for lock player in the window
    void render(SDL_Renderer* renderer); // Function for display sprite of player
    void handleInput(const bool* keys, float dt); // Function for interation with the keyboard
	void shoot(); // Function for shoot
	void HUD(SDL_Renderer* renderer, SDL_Texture* heart, int HP, int Score); // Function for display HUD
    void Collide(std::vector<Enemy>& enemies); // Function for check collision

    ~Entity();
};