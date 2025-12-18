#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include "Hero.h"
#include "Screen.h"
#include "Enemy.h"

int main(int argc, char** argv) {
    bool restart = true;
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<Enemy>enemies;

    const int FPS = 60;
    const int FRAME_DELAY = 1000 / FPS;

    Uint64 frameStart;
    int frameTime;

    if (SDL_Init(SDL_INIT_VIDEO) < 0 || !SDL_CreateWindowAndRenderer("SHOOT'EM UP", 640, 480, SDL_WINDOW_FULLSCREEN, &window, &renderer))
        return 1;
    if (TTF_Init() < 0) {
        SDL_Log("Erreur SDL_ttf : %s", SDL_GetError());
        return 1;
    }

    SDL_Surface* surface = IMG_Load("picture/arena.png");
    SDL_Texture* background = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    Entity player(400.0f, 300.0f, 150, 150, SDL_Color{ 255, 0, 0, 255 }, 400);
    player.loadTexture(renderer, "picture/player.png");
    player.loadBulletTexture(renderer, "picture/bullet.png");

    SDL_Texture* heart = nullptr;
    SDL_Surface* surface2 = IMG_Load("picture/heart.png");
    if (surface2) {
        heart = SDL_CreateTextureFromSurface(renderer, surface2);
        SDL_DestroySurface(surface);
        SDL_SetTextureScaleMode(heart, SDL_SCALEMODE_NEAREST);
    }
    else {
        SDL_Log("Erreur chargement bullet: %s", SDL_GetError());
    }

    SDL_Texture* enemyTexture = nullptr;
    SDL_Surface* surface3 = IMG_Load("picture/bomb.png");
    if (surface3) {
        enemyTexture = SDL_CreateTextureFromSurface(renderer, surface3);
        SDL_DestroySurface(surface3);
        SDL_SetTextureScaleMode(enemyTexture, SDL_SCALEMODE_NEAREST);
    }
    else {
        SDL_Log("Erreur chargement bullet: %s", SDL_GetError());
    }

    SDL_Texture* home = nullptr;
    SDL_Surface* surface4 = IMG_Load("picture/home.png");
    if (surface4) {
        home = SDL_CreateTextureFromSurface(renderer, surface4);
        SDL_DestroySurface(surface4);
        SDL_SetTextureScaleMode(home, SDL_SCALEMODE_NEAREST);
    }
    else {
        SDL_Log("Erreur chargement bullet: %s", SDL_GetError());
    }

    Uint64 last_time = SDL_GetTicks();
    bool keepGoing = true;
    GameState screen = MENU;

    int menuSelection = 0;
    bool enterPressed = false;

    while (keepGoing) {
        if (restart) {
            player.HP = 4;
            player.Score = 0;
            player.bullets.clear();
            player.rect.x = 400.0f;
            player.rect.y = 300.0f;
            player.timeSinceLastShot = 0.0f;
            enemies.clear();
            restart = false;
        }
        float dt = (SDL_GetTicks() - last_time) / 1000.0f;
        last_time = SDL_GetTicks();
        frameStart = SDL_GetTicks();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                keepGoing = false;
                screen = QUIT;
            }
            NavigateMenu(screen, event, menuSelection, enterPressed);
        }

        screen = updateGameState(screen, renderer, background, player, dt, window, enemies, player.bullets, enemyTexture, heart, restart, home);

        frameTime = SDL_GetTicks() - frameStart;

        if (frameTime < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }

        if (screen == QUIT) {
            keepGoing = false;
        }
    }

    SDL_DestroyTexture(background);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}