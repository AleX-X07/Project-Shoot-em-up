#pragma once
// Librairie externe
#include <iostream>
#include <string>
#include <vector>

// Load SDL
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

// Load file
#include "Bullet.h"


// Foraward declaration for Enemy
class Enemy;

// Class Entity for play, who inherit from bullet
class Hero : public Bullet { 

public:

    // Variable for position/dimension
    SDL_FRect rect;

    // Vector for bullet
    std::vector<Bullet> heroBullets;

    // Variable for his characteristic
    int HP = 4;
    int score = 0;
    float speed;
    int nbr_enemy_death = 0;
    int bossDeath = 0;

    SDL_Texture* texture = nullptr;

    // Variable for calculate cooldown
    float shootCooldown = 0.15f;      
    float timeSinceLastShot = 0;
	
    float collisionCooldownEnemy = 0.5f;
    float timeSinceLastHit = 0;

    float collisionCooldownBulletEnemy = 0.2f;
    float timeSinceLastHitBullet = 0;

    // Constructor
    Hero();
    Hero(float x, float y, float w, float h, float _speed);

    //Render/Update
    void render(SDL_Renderer* renderer); 
    void updateInput(const bool* keys, float dt);

    // Function for lock in window
    void clampToScreen(int screenWidth, int screenHeight);

    // Function for shoot
	void shoot(); 

    // Function for display HUD
	void HUD(SDL_Renderer* renderer, SDL_Texture* heart, int HP, int Score); 

    // Function for collision
    void CollideBullet(std::vector<Enemy>& enemies); 
    void CollideEnemy(std::vector<Enemy>& enemies, float dt); 
    void CollideEnemyBullet(std::vector<Enemy>& enemies, float dt);
};