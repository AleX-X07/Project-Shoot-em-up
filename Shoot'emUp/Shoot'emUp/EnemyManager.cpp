#include "EnemyManager.h"
#include <algorithm>

EnemyManager::EnemyManager() {
    lastSpawn = SDL_GetTicks();
    lastClassicSpawn = SDL_GetTicks();
    lastTripleSpawn = SDL_GetTicks();

    spawnInterval = 2000;
    classicSpawnInterval = 3000;
    tripleSpawnInterval = 5000;
}

void EnemyManager::spawn(int windowWidth, int windowHeight, Uint32 now) {
    if (now - lastSpawn > spawnInterval) {
        spawnEnemy(enemies, windowWidth, windowHeight);
        lastSpawn = now;
    }
    if (now - lastClassicSpawn > classicSpawnInterval) {
        Classic_enemy::spawnClassicEnemy(classics, windowWidth, windowHeight);
        lastClassicSpawn = now;
    }
    if (now - lastTripleSpawn > tripleSpawnInterval) {
        ShootMultiple_Enemy::spawnShootMultipleEnemy(triples, windowWidth, windowHeight);
        lastTripleSpawn = now;
    }
}

void EnemyManager::update(int windowWidth, Uint32 now) {
    updateEnemies(enemies);

    for (auto& c : classics) {
        c.update(windowWidth);
        c.shoot(projectiles, now);
    }

    for (auto& t : triples) {
        t.update(windowWidth);
        t.shoot(projectiles, now);
    }

    for (auto& p : projectiles) {
        p.x += p.speed;
        p.y += p.speedY;
    }
}

void EnemyManager::render(SDL_Renderer* renderer) {
    renderEnemies(renderer, enemies);

    for (auto& c : classics) {
        c.render(renderer);
    }

    for (auto& t : triples) {
        t.render(renderer);
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    for (auto& p : projectiles) {
        SDL_FRect rect = { p.x, p.y, p.w, p.h };
        SDL_RenderFillRect(renderer, &rect);
    }
}

void EnemyManager::cleanProjectiles() {
    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
        [](const Projectile& p) { return p.x + p.w < 0; }),
        projectiles.end());
}

void EnemyManager::DisplayEnnemy(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* background) {
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    Uint32 now = SDL_GetTicks();
    if (now - lastSpawn > spawnInterval) {
        spawnEnemy(enemies, windowWidth, windowHeight);
        lastSpawn = now;
    }
    if (now - lastClassicSpawn > classicSpawnInterval) {
        Classic_enemy::spawnClassicEnemy(classics, windowWidth, windowHeight);
        lastClassicSpawn = now;
    }
    if (now - lastTripleSpawn > tripleSpawnInterval) {
        ShootMultiple_Enemy::spawnShootMultipleEnemy(triples, windowWidth, windowHeight);
        lastTripleSpawn = now;
    }
    // === UPDATE ===
    updateEnemies(enemies);
    for (auto& c : classics) {
        c.update(windowWidth);
        c.shoot(projectiles, now);
    }
    for (auto& t : triples) {
        t.update(windowWidth);
        t.shoot(projectiles, now);
    }
    for (auto& p : projectiles) {
        p.x += p.speed;
        p.y += p.speedY;
    }
    // Nettoyer projectiles hors écran
    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
        [](const Projectile& p) { return p.x + p.w < 0; }),
        projectiles.end());
    // === RENDER ===
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, background, NULL, NULL);
    renderEnemies(renderer, enemies);
    for (auto& c : classics) {
        c.render(renderer);
    }
    for (auto& t : triples) {
        t.render(renderer);
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    for (auto& p : projectiles) {
        SDL_FRect rect = { p.x, p.y, p.w, p.h };
        SDL_RenderFillRect(renderer, &rect);
    }
    spawn(windowWidth, windowHeight, now);
    update(windowWidth, now);
    cleanProjectiles();
    // Rendu
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, background, NULL, NULL);
    render(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(16);
}