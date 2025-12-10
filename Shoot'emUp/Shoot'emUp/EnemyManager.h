//#pragma once
//#include <vector>
//#include <SDL3/SDL.h>
//#include "Enemy.h"
//#include "Classic_enemy.h"
//#include "ShootMultiple_Enemy.h"
//
//class EnemyManager {
//private:
//    std::vector<Enemy> enemies;
//    std::vector<Classic_enemy> classics;
//    std::vector<ShootMultiple_Enemy> triples;
//    std::vector<Projectile> projectiles;
//
//    Uint32 lastSpawn;
//    Uint32 lastClassicSpawn;
//    Uint32 lastTripleSpawn;
//
//    Uint32 spawnInterval;
//    Uint32 classicSpawnInterval;
//    Uint32 tripleSpawnInterval;
//
//public:
//    EnemyManager();
//
//    void spawn(int windowWidth, int windowHeight, Uint32 now);
//    void update(int windowWidth, Uint32 now);
//    void render(SDL_Renderer* renderer);
//    void cleanProjectiles();
//};