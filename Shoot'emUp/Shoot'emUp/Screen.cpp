#include "Screen.h"
#include <SDL3/SDL.h>

GameState updateGameState(GameState screen, SDL_Renderer* renderer, SDL_Texture* background, Entity& player, float dt, SDL_Window* window) {
    int w, h;
    static int menuSelection = 0; // 0 = Play, 1 = Quit
    static bool upPressed = false;
    static bool downPressed = false;
    static bool enterPressed = false;


    const bool* keys = SDL_GetKeyboardState(NULL);

    switch (screen) {
    case MENU: {

        SDL_SetRenderDrawColor(renderer, 0, 0, 50, 255);
        SDL_RenderClear(renderer);

        SDL_GetWindowSize(window, &w, &h);

        // --- Titre ---
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_FRect titleRect = { (float)(w / 2 - 200), 100, 400, 80 };
        SDL_RenderRect(renderer, &titleRect);

        // --- Option PLAY ---
        int playY = h / 2 - 40;
        SDL_FRect playRect = { (float)(w / 2 - 100), (float)playY, 200, 50 };
        if (menuSelection == 0) {
            SDL_SetRenderDrawColor(renderer, 100, 255, 100, 255);
            SDL_RenderFillRect(renderer, &playRect);
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderRect(renderer, &playRect);

        // --- Option QUIT ---
        int quitY = h / 2 + 40;
        SDL_FRect quitRect = { (float)(w / 2 - 100), (float)quitY, 200, 50 };
        if (menuSelection == 1) {
            SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255);
            SDL_RenderFillRect(renderer, &quitRect);
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderRect(renderer, &quitRect);

        SDL_RenderPresent(renderer);

        // --- Navigation menu ---
        if (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W]) {
            if (!upPressed) {
                menuSelection = (menuSelection - 1 + 2) % 2;
                upPressed = true;
            }
        }
        else upPressed = false;

        if (keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S]) {
            if (!downPressed) {
                menuSelection = (menuSelection + 1) % 2;
                downPressed = true;
            }
        }
        else downPressed = false;

        // --- Validation ---
        if (keys[SDL_SCANCODE_RETURN]) {
            if (!enterPressed) {
                enterPressed = true;
                if (menuSelection == 0) return LEVEL1;
                if (menuSelection == 1) return QUIT;
            }
        }
        else enterPressed = false;

        break;
    }

    case LEVEL1: {

        player.handleInput(keys, dt);
        SDL_GetWindowSize(window, &w, &h);
        player.clampToScreen(w, h);
        player.updateBullets(dt);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, background, NULL, NULL);

        player.render(renderer);
        player.renderBullets(renderer);
        player.DisplayHP(renderer, player.HP);

        SDL_RenderPresent(renderer);

        if (keys[SDL_SCANCODE_ESCAPE]) {
            player.HP = 3;
            player.bullets.clear();
            player.rect.x = 400.0f;
            player.rect.y = 300.0f;
            return MENU;
        }
        break;
    }

    case QUIT:
        break;
    }

    return screen;
}