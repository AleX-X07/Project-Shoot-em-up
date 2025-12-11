#include "Screen.h"
#include "Menu.h"
#include "EnemyManager.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>

GameState updateGameState(GameState screen,Entity& player,float dt,SDL_Window* window,EnemyManager* enemyManager) {
    int w, h;
    static int menuSelection = 0; // 0 = Play, 1 = Quit
    static bool upPressed = false;
    static bool downPressed = false;
    static bool enterPressed = false;

    const bool* keys = SDL_GetKeyboardState(NULL);

    switch (screen) {
    case MENU: {
        // --- Navigation menu ---
        if (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W]) {
            if (!upPressed) {
                menuSelection = (menuSelection - 1 + 2) % 2;
                upPressed = true;
            }
        }
        else {
            upPressed = false;
        }

        if (keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S]) {
            if (!downPressed) {
                menuSelection = (menuSelection + 1) % 2;
                downPressed = true;
            }
        }
        else {
            downPressed = false;
        }

        // --- Validation ---
        if (keys[SDL_SCANCODE_RETURN]) {
            if (!enterPressed) {
                enterPressed = true;
                if (menuSelection == 0) return LEVEL1;
                if (menuSelection == 1) return QUIT;
            }
        }
        else {
            enterPressed = false;
        }

        break;
    }

    case LEVEL1: {
        const bool* keys = SDL_GetKeyboardState(NULL);

        player.handleInput(keys, dt);
        SDL_GetWindowSize(window, &w, &h);
        player.clampToScreen(w, h);
        player.updateBullets(dt);

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




void NavigateMenu(GameState screen, SDL_Event event, bool keepgoing) {
    int menuSelection = 0;
    bool enterPressed = false;
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

void renderGame(GameState screen,
    SDL_Renderer* renderer,
    SDL_Texture* background,
    SDL_Window* window,
    Entity& player,
    EnemyManager* enemyManager,
    TTF_Font* font) {
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    SDL_Color white = { 255, 255, 255, 255 };

    switch (screen) {
    case MENU: {
        SDL_SetRenderDrawColor(renderer, 0, 0, 50, 255);
        SDL_RenderClear(renderer);

        TitleMenu(renderer, w, h, white, "SHOOT'EM UP", font,
            w / 2 - 200, 200, 400, 80);

        // ⚠ ici, il te faut soit récupérer `menuSelection`,
        // soit le passer en paramètre à renderGame
        extern int gMenuSelection; // si tu veux un global temporaire
        ButtonMenu(renderer, w, h, white, "PLAY", font,
            w / 2 - 100, h / 2 - 60, 200, 50, gMenuSelection, 0);
        ButtonMenu(renderer, w, h, white, "QUIT", font,
            w / 2 - 100, h / 2 + 20, 200, 50, gMenuSelection, 1);
        break;
    }

    case LEVEL1: {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, background, NULL, NULL);

        player.render(renderer);
        player.renderBullets(renderer);
        player.DisplayHP(renderer, player.HP);
        enemyManager->DisplayEnnemy(window, renderer, background);
        break;
    }

    case QUIT:
        // Optionnel : écran de sortie
        break;
    }

    SDL_RenderPresent(renderer);
}