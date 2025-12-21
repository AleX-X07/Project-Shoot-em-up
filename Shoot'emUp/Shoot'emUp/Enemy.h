#pragma once
#include <vector>
#include <random>
#include "SDL3/SDL.h"
#include "Hero.h"
#include "LoadRessource.h"
#include "Level.h"

class Enemy
{
public:
    float x, y;
    float w, h;
    float speed;
    SDL_FRect rect;
    std::vector<Enemy>enemies;
    std::vector<Bullet>enemiesBullet;
    SDL_Color color;
    int HP;
    int HPmax;
    int Value;
    int numEnemy;


    SDL_Texture* enemyTextureBomb;
    SDL_Texture* enemyTextureShooter;
    SDL_Texture* bulletEnemyTexture;
    SDL_Texture* bossTexture;

    Uint32 lastShotTime = 0;
    Uint32 lastSpawnTime = 0;
    Uint32 now = SDL_GetTicks();

    Enemy();
    Enemy(float _x, float _y, float _w, float _h, float _speed, SDL_Color color);

    static int randomInt(int min, int max);
    void clampToScreenEnemy(int w, int h);

    static void updateEnemy(std::vector<Enemy>& enemies, float dt, int screenWidth, int screenHeight);
    static void renderEnemy(SDL_Renderer* renderer, const std::vector<Enemy>& enemies);

    static void spawnEnemyBomb(std::vector<Enemy>& enemies, int windowWidth, int windowHeight, SDL_Renderer* renderer, SDL_Texture* sharedTexture);
    static void spawnEnemyShooter(std::vector<Enemy>& enemies, int windowWidth, int windowHeight, SDL_Renderer* renderer, SDL_Texture* sharedTexture, SDL_Texture* sharedTextureBulet);
    static void spawnEnemyShooterV2(std::vector<Enemy>& enemies, int windowWidth, int windowHeight, SDL_Renderer* renderer, SDL_Texture* sharedTexture, SDL_Texture* sharedTextureBulet);
    static void spawnEnemyBoss(std::vector<Enemy>& enemies, int windowWidth, int windowHeight, SDL_Renderer* renderer, LoadRessource& MyRessource);

    void shoot(std::vector<Bullet>& enemiesBullet);
    void shootV2(std::vector<Bullet>& enemiesBullet);
    void shootBoss(std::vector<Bullet>& enemiesBullet);

    static void EnemyManager(std::vector<Enemy>& enemies, SDL_Renderer* renderer, int windowWidth, int windowHeight, LoadRessource& MyRessource, Level& MyLevel1);

    ~Enemy();
};