#include "EnemyManager.h"
#include <algorithm>
#include "Bullet.h"

EnemyManager::EnemyManager()
    : lastSpawn(SDL_GetTicks()),
    lastClassicSpawn(SDL_GetTicks()),
    lastTripleSpawn(SDL_GetTicks()),
    spawnInterval(2000),
    classicSpawnInterval(3000),
    tripleSpawnInterval(5000) {
}

void EnemyManager::spawn(int windowWidth, int windowHeight, Uint32 now) {
    if (now - lastSpawn > spawnInterval) {
        Enemy::spawn(enemies, windowWidth, windowHeight);
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
    EnemyManager::update(enemies);

    for (auto& c : classics) {
        c.update(windowWidth);
        c.shoot(bullets, now);
    }

    for (auto& t : triples) {
        t.update(windowWidth);
        t.shoot(projectiles, now);
    }

    for (auto& p : bullets) {
        p.x += p.speed;
        p.y += p.speedY;
    }
}

void EnemyManager::render(SDL_Renderer* renderer) {
    Enemy::render(renderer, enemies);

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

void EnemyManager::renderHealthBar(SDL_Renderer* renderer)
{
    // Fond de la barre (rouge)
    SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255);
    SDL_FRect bgRect = { barX, barY, barWidth, barHeight };
    SDL_RenderFillRect(renderer, &bgRect);

    // Barre de vie (vert)
    float healthPercent = currentHealth / maxHealth;
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_FRect healthRect = { barX, barY, barWidth * healthPercent, barHeight };
    SDL_RenderFillRect(renderer, &healthRect);

    // Contour de la barre (noir)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderRect(renderer, &bgRect);
}