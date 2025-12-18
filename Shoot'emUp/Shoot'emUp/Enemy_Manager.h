#pragma once
#include <vector>
#include <SDL3/SDL.h>
#include "Enemy.h"
#include "Shooter_Enemy.h"
#include "ShootMultiple_Enemy.h"
#include "Bullet.h"
#include <algorithm>


class EnemyManager {
public:
    std::vector<Enemy> enemies;
    std::vector<Shooter_Enemy> Shooter;
    std::vector<ShootMultiple_Enemy> triples;
    std::vector<Bullet> bullets;
    std::vector<EnemyManager>Manager;
    Uint32 lastSpawn;
    Uint32 lastShooterEnemySpawn;
    Uint32 lastTripleSpawn;

    SDL_Renderer* renderer;
    SDL_Texture* enemyTexture;

    Uint32 spawnInterval;
    Uint32 ShooterEnemySpawnInterval;
    Uint32 tripleSpawnInterval;

    float x, y;
    float w, h;
    float speed;
    float maxHealth;
    float currentHealth;
    float barWidth = w;
    float barHeight = 5;
    float barX = x;
    float barY = y - 10;

    public:


    EnemyManager();

    void spawn(int windowWidth, int windowHeight, Uint32 now);
    void update(int windowWidth, Uint32 now);
    void render(SDL_Renderer* renderer);
    void cleanBullet();
    void renderHealthBar(SDL_Renderer* renderer);

};
