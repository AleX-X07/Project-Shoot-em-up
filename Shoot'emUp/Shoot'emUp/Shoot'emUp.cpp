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

    // Variables pour les ennemis rouges
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    std::vector<Enemy> enemies;
    Uint32 lastSpawn = SDL_GetTicks();
    Uint32 spawnInterval = 2000; // toutes les 2 secondes

    std::vector<Classic_enemy> classics;
    Uint32 lastClassicSpawn = SDL_GetTicks();
    Uint32 classicSpawnInterval = 3000; // toutes les 3 secondes
    std::vector<Projectile> projectiles;


    // --- Classic_enemy ---
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    Classic_enemy classic(
        windowWidth,                       // spawn à droite
        std::rand() % (windowHeight - 50), // position Y aléatoire
        50,                                // largeur
        50,                                // hauteur
        2                                  // vitesse
    );

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
        }

        SDL_GetWindowSize(window, &windowWidth, &windowHeight);

        // Spawn ennemi rouge
        Uint32 now = SDL_GetTicks();
        if (now - lastSpawn > spawnInterval) {
            spawnEnemy(enemies, windowWidth, windowHeight);
            lastSpawn = now;
        }

        updateEnemies(enemies);

        // Spawn Classic_enemy
    	if (now - lastClassicSpawn > classicSpawnInterval) {
            Classic_enemy::spawnClassicEnemy(classics, windowWidth, windowHeight);
            lastClassicSpawn = now;
        }

        // Update Classic_enemy
        for (auto& c : classics) {
            c.update(windowWidth);
            c.shoot(projectiles, now);
        }

        // Render Classic_enemy
        for (auto& c : classics) {
            c.render(renderer);  // Appel sur l'instance
        }


		// Update projectiles
		for (auto& p : projectiles) {
		    p.x += p.speed;
		}
		projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
		    [](const Projectile& p) { return p.x + p.w < 0; }),
		    projectiles.end());


		// Render projectiles
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
		for (auto& p : projectiles) {
		    SDL_FRect rect = { p.x, p.y, p.w, p.h };
		    SDL_RenderFillRect(renderer, &rect);
		}

        // --- Update Classic_enemy ---
        classic.update(windowWidth);
        classic.shoot(projectiles, now);

        // Update projectiles
        for (auto& p : projectiles) {
            p.x += p.speed;
        }
        // Nettoyer projectiles hors écran
        projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
            [](const Projectile& p) { return p.x + p.w < 0; }),
            projectiles.end());

        // Effacer l'écran
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Dessiner le fond
        SDL_RenderTexture(renderer, background, NULL, NULL);

        // Dessiner les ennemis rouges
        renderEnemies(renderer, enemies);

        // Dessiner tous les Classic_enemy
        for (auto& c : classics) {
            c.render(renderer);
        }

        // Dessiner les projectiles
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // jaune
        for (auto& p : projectiles) {
            SDL_FRect rect = { p.x, p.y, p.w, p.h };
            SDL_RenderFillRect(renderer, &rect);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // ~60 FPS
    }

    SDL_DestroyTexture(background);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
