#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Hero.h"
#include "Screen.h"

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