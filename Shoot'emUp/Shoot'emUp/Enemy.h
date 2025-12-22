#pragma once
// Librairie externe
#include <vector>
#include <random>

// Load SLD
#include "SDL3/SDL.h"

// Load file
#include "Hero.h"
#include "LoadRessource.h"
#include "Level.h"

// Class Enemy
class Enemy
{

public:

    // Variable for position/dimension
    float x, y;
    float w, h;
    SDL_FRect rect;

    // Vector for enemy and his bullet
    std::vector<Enemy>enemies;
    std::vector<Bullet>enemiesBullet;

    // Variable for his characteristic
    int HP;
    int HPmax;
    float speed;
    int Value;
    int numEnemy;

    // Texture for each enemy
    SDL_Texture* enemyTextureBomb;
    SDL_Texture* enemyTextureShooter;
    SDL_Texture* bossTexture;

    // Texture for bullet enemy
    SDL_Texture* bulletEnemyTexture;

    // Variable for time spawn
    Uint32 lastShotTime = 0;
    Uint32 lastSpawnTime = 0;
    Uint32 now = SDL_GetTicks();

    // Constructor
    Enemy();
    Enemy(float _x, float _y, float _w, float _h, float _speed);

    // Random
    static int randomInt(int min, int max);

    // Lock enemy in the window
    void clampToScreenEnemy(int w, int h);

    // Function render/update
    static void updateEnemy(std::vector<Enemy>& enemies, float dt, int screenWidth, int screenHeight, Hero& player);
    static void renderEnemy(SDL_Renderer* renderer, const std::vector<Enemy>& enemies);

    // Function for spawn
    static void spawnEnemyBomb(std::vector<Enemy>& enemies, int windowWidth, int windowHeight, SDL_Renderer* renderer, SDL_Texture* sharedTexture);
    static void spawnEnemyShooter(std::vector<Enemy>& enemies, int windowWidth, int windowHeight, SDL_Renderer* renderer, SDL_Texture* sharedTexture, SDL_Texture* sharedTextureBulet);
    static void spawnEnemyShooterV2(std::vector<Enemy>& enemies, int windowWidth, int windowHeight, SDL_Renderer* renderer, SDL_Texture* sharedTexture, SDL_Texture* sharedTextureBulet);
    static void spawnEnemyBoss(std::vector<Enemy>& enemies, int windowWidth, int windowHeight, SDL_Renderer* renderer, LoadRessource& MyRessource);

    static void EnemyManager(std::vector<Enemy>& enemies, SDL_Renderer* renderer, int windowWidth, int windowHeight, LoadRessource& MyRessource, Level& MyLevel1);

    // Function for shoot
    void shoot(std::vector<Bullet>& enemiesBullet);
    void shootV2(std::vector<Bullet>& enemiesBullet);
    void shootBoss(std::vector<Bullet>& enemiesBullet);
};