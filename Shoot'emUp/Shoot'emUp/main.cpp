#include <SDL3/SDL.h> // Librairie externe
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include "Hero.h"
#include "Screen.h"
#include "Enemy.h"
#include "LoadRessource.h"
#include "Level.h"

int main(int argc, char** argv) {

    bool restart = true;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Enemy MyEnemy;

    const int FPS = 60;
    const int FRAME_DELAY = 1000 / FPS;

    Uint64 frameStart;
    int frameTime;

    if (SDL_Init(SDL_INIT_VIDEO) < 0 || !SDL_CreateWindowAndRenderer("SHOOT'EM UP", 640, 480, SDL_WINDOW_FULLSCREEN, &window, &renderer)) // Initialisation window
        return 1;
    if (TTF_Init() < 0) {
        SDL_Log("Erreur SDL_ttf : %s", SDL_GetError());
        return 1;
    }

    LoadRessource MyRessource = LoadRessource(renderer);
    Level MyLevel1 = Level(2,2,2,1);
    MyRessource.loadAllTexture();
    Entity player(400.0f, 300.0f, 100, 100, SDL_Color{ 255, 0, 0, 255 }, 400);
    player.texture = MyRessource.entityTexture;
    player.bulletTexture = MyRessource.bulletTexture;

    Uint64 last_time = SDL_GetTicks();
    bool keepGoing = true;
    GameState screen = MENU;

    int menuSelection = 0;
    bool enterPressed = false;

    while (keepGoing) { // Loop for reload level
        if (restart) {
            player.HP = 4;
            player.Score = 0;
            player.bullets.clear();
            player.rect.x = 400.0f;
            player.rect.y = 300.0f;
            player.timeSinceLastShot = 0.0f;
            MyEnemy.enemies.clear();
            restart = false;
        }
        float dt = (SDL_GetTicks() - last_time) / 1000.0f; // Computes the time elapsed (in seconds) since the previous frame.
        last_time = SDL_GetTicks();
        frameStart = SDL_GetTicks();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {  // Touch keyboard for choice in menu
            if (event.type == SDL_EVENT_QUIT) {
                keepGoing = false;
                screen = QUIT;
            }
            NavigateMenu(screen, event, menuSelection, enterPressed);
        }

        screen = updateGameState(screen, renderer, MyRessource, player, dt, window, MyEnemy.enemies, player.bullets, restart, MyLevel1); // Update the game (Menu,Level1,Level2,GameOver)

        frameTime = SDL_GetTicks() - frameStart;

        if (frameTime < FRAME_DELAY) { // Delay for 60FPS
            SDL_Delay(FRAME_DELAY - frameTime);
        }

        if (screen == QUIT) {
            keepGoing = false;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}