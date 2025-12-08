#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "Enemy.h"
#include "Classic_enemy.h"


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

    // Charger une image de fond
    SDL_Surface* surface = IMG_Load("arena.png");
    if (!surface) {
        SDL_Log("Erreur chargement image: %s", SDL_GetError());
        return 1;
    }
    SDL_Texture* background = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    // Variables pour les ennemis
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    std::vector<Enemy> enemies;
    Uint32 lastSpawn = SDL_GetTicks();
    Uint32 spawnInterval = 2000; // toutes les 2 secondes

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
        }

        // Récupérer la taille de la fenêtre
        int windowWidth, windowHeight;
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);

        // Spawn ennemi
        Uint32 now = SDL_GetTicks();
        if (now - lastSpawn > spawnInterval) {
            spawnEnemy(enemies, windowWidth, windowHeight);
            lastSpawn = now;
        }

        updateEnemies(enemies);

        // Effacer l'écran
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Dessiner le fond
        SDL_RenderTexture(renderer, background, NULL, NULL);

        // Dessiner les ennemis
        renderEnemies(renderer, enemies);

        // Afficher
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // ~60 FPS
    }
    Uint32 now = SDL_GetTicks();

    // Vecteurs globaux
    std::vector<Classic_enemy> e;
    std::vector<Projectile> projectiles;

    // Exemple : un ennemi qui se déplace
    e.push_back(Classic_enemy(600, 200, 50, 50, 3));

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
        }

        Uint32 now = SDL_GetTicks();

        // Tir des ennemis
        for (auto& e : enemies) {
            e.shoot(projectiles, now);
        }

        // Mise à jour projectiles
        updateProjectiles(projectiles);

        // Effacer l'écran
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Dessiner le fond
        SDL_RenderTexture(renderer, background, NULL, NULL);

        // Dessiner les ennemis
        renderEnemies(renderer, enemies);

        // Dessiner les projectiles
        renderProjectiles(renderer, projectiles);

        SDL_RenderPresent(renderer);

        SDL_Delay(16); // ~60 FPS
    }



    SDL_DestroyTexture(background);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
