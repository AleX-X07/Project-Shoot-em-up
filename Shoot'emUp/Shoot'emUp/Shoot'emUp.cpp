#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "Enemy.h"
#include "Classic_enemy.h"
#include "ShootMultiple_Enemy.h"


int main(int argc, char** argv) {
    SDL_Window* window;
    SDL_Renderer* renderer;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Erreur SDL: %s", SDL_GetError());
        return 1;
    }
    if (!SDL_CreateWindowAndRenderer("HELLO SDL", 640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Erreur création fenêtre/rendu: %s", SDL_GetError());
        return 1;
    }
    // Charger image de fond
    SDL_Surface* surface = IMG_Load("arena.png");
    if (!surface) {
        SDL_Log("Erreur chargement image: %s", SDL_GetError());
        return 1;
    }
    SDL_Texture* background = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    // Initialisation
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    int windowWidth, windowHeight;
    // Vecteurs d'ennemis et projectiles
    std::vector<Enemy> enemies;
    std::vector<Classic_enemy> classics;
    std::vector<ShootMultiple_Enemy> triples;
    std::vector<Projectile> projectiles;
    // Timers de spawn
    Uint32 lastSpawn = SDL_GetTicks();
    Uint32 lastClassicSpawn = SDL_GetTicks();
    Uint32 lastTripleSpawn = SDL_GetTicks();
    Uint32 spawnInterval = 2000;
    Uint32 classicSpawnInterval = 3000;
    Uint32 tripleSpawnInterval = 5000;
    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
        }
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
        Uint32 now = SDL_GetTicks();
        // === SPAWN ===
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
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    SDL_DestroyTexture(background);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}