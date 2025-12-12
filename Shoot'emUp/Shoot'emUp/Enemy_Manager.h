#pragma once
#include <vector>
#include <SDL3/SDL.h>
#include "Enemy.h"
#include "Shooter_Enemy.h"
//#include "ShootMultiple_Enemy.h"
#include "Bullet.h"


class EnemyManager {
private:
    std::vector<Enemy> enemies;
    std::vector<Shooter_Enemy> Shooter;
    //std::vector<ShootMultiple_Enemy> triples;
    std::vector<Bullet> bullets;

    Uint32 lastSpawn;
    Uint32 lastShooterEnemySpawn;
    //Uint32 lastTripleSpawn;

    Uint32 spawnInterval;
    Uint32 ShooterEnemySpawnInterval;
    //Uint32 tripleSpawnInterval;




public:

    float x, y;
    float w, h;
    float speed;
    float maxHealth;
    float currentHealth;
    float barWidth = w;
    float barHeight = 5;
    float barX = x;
    float barY = y - 10;

    EnemyManager();

    void spawn(int windowWidth, int windowHeight, Uint32 now);
    void update(int windowWidth, Uint32 now);
    void render(SDL_Renderer* renderer);
    void cleanBullet(std::vector<Bullet>& bullets);
    void renderHealthBar(SDL_Renderer* renderer);
};
