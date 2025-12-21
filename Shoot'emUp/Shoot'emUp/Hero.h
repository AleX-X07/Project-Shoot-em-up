#pragma once
#include <iostream>
#include <SDL3/SDL.h>
#include <vector>
#include <SDL3_image/SDL_image.h>
#include "Bullet.h"
#include <string>
#include <SDL3_ttf/SDL_ttf.h>

class Enemy;

class Entity : public Bullet { // Class for player
public:

    SDL_FRect rect;
    SDL_Texture* texture;
    SDL_Color color;
    std::vector<Bullet> heroBullets;

    int HP = 4;
    int Score = 0;
    float speed;

    int nbr_enemy_death;
    int bossDeath;

    float shootCooldown = 0.15f;      
    float timeSinceLastShot = 0.0f;
	
    float collisionCooldownEnemy = 0.5f;
    float timeSinceLastHit = 0.0f;

    float collisionCooldownBulletEnemy = 0.2f;
    float timeSinceLastHitBullet = 0.0f;

    Entity();
    Entity(float x, float y, float w, float h, SDL_Texture* tex, float spd = 200.0f);
    Entity(float x, float y, float w, float h, SDL_Color col, float spd = 200.0f);

    void move(float dx, float dy, float dt); // Function for move player
    void clampToScreen(int screenWidth, int screenHeight); // Function for lock player in the window
    void render(SDL_Renderer* renderer); // Function for display sprite of player
    void handleInput(const bool* keys, float dt); // Function for interation with the keyboard
	void shoot(); // Function for shoot
	void HUD(SDL_Renderer* renderer, SDL_Texture* heart, int HP, int Score); // Function for display HUD
    void CollideBullet(std::vector<Enemy>& enemies); // Function for check collision between bullet of hero and enemy
    void CollideEnemy(std::vector<Enemy>& enemies, float dt); // Function for check collision between an enemy and hero
    void CollideEnemyBullet(std::vector<Enemy>& enemies, float dt); // Function for check collision between a bullet enemy and hero

    ~Entity();
};