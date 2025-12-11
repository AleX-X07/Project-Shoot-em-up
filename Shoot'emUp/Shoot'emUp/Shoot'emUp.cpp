#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "Hero.h"
#include "Screen.h"
#include "Enemy.h"
#include "Classic_enemy.h"
#include "ShootMultiple_Enemy.h"

int main(int argc, char** argv) {
    SDL_Window* window;
    SDL_Renderer* renderer;

    if (SDL_Init(SDL_INIT_VIDEO) < 0 || !SDL_CreateWindowAndRenderer("SHOOT'EM UP", 640, 480, SDL_WINDOW_FULLSCREEN, &window, &renderer))
        return 1;
    if (TTF_Init() < 0) {
        SDL_Log("Erreur SDL_ttf : %s", SDL_GetError());
        return 1;
    }
    SDL_Surface* surface = IMG_Load("picture/arena.png");
    SDL_Texture* background = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    Entity player(400.0f, 300.0f, 200, 200, SDL_Color{ 255, 0, 0, 255 }, 400);
    player.loadTexture(renderer, "picture/player.png");
    player.loadBulletTexture(renderer, "picture/bullet.png");

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

    Uint64 last_time = SDL_GetTicks();
    bool keepGoing = true;
    GameState screen = MENU;

    int menuSelection = 0; 
    bool enterPressed = false;

    while (keepGoing) {
        float dt = (SDL_GetTicks() - last_time) / 1000.0f;
        last_time = SDL_GetTicks();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                keepGoing = false;
                screen = QUIT;
            }

            if (screen == MENU && event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.key == SDLK_UP || event.key.key == SDLK_W) {
                    menuSelection = (menuSelection - 1 + 2) % 2;
                }
                if (event.key.key == SDLK_DOWN || event.key.key == SDLK_S) {
                    menuSelection = (menuSelection + 1) % 2;
                }
                if (event.key.key == SDLK_RETURN && !enterPressed) {
                    enterPressed = true;
                    if (menuSelection == 0) {
                        screen = LEVEL1;
                    }
                    else if (menuSelection == 1) {
                        screen = QUIT;
                    }
                }
                if (event.key.key == SDLK_ESCAPE) {
                    screen = QUIT;
                }
            }

            if (event.type == SDL_EVENT_KEY_UP) {
                if (event.key.key == SDLK_RETURN) {
                    enterPressed = false;
                }
            }

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
        screen = updateGameState(screen, renderer, background, player, dt, window);

        if (screen == QUIT) keepGoing = false;
    }
    SDL_DestroyTexture(background);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}