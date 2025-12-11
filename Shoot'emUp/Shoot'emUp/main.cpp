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
#include "EnemyManager.h"


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
    EnemyManager* enemyManager = new EnemyManager();
    player.loadTexture(renderer, "picture/player.png");
    player.loadBulletTexture(renderer, "picture/bullet.png");

    Uint64 last_time = SDL_GetTicks();
    bool keepGoing = true;
    GameState screen = MENU;

    while (keepGoing) {
        float dt = (SDL_GetTicks() - last_time) / 1000.0f;
        last_time = SDL_GetTicks();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                keepGoing = false;
                screen = QUIT;
            }
        }

        screen = updateGameState(screen, player, dt, window, enemyManager);
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