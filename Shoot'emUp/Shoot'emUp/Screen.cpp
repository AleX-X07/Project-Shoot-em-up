#include "Screen.h"
#include "Menu.h"
#include "Enemy.h"
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>

float collisionCooldown = 0.5f;
float timeSinceLastHit = 0.0f;

GameState updateGameState(GameState screen, SDL_Renderer* renderer, SDL_Texture* background, Entity& player, float dt, SDL_Window* window, std::vector<Enemy>& enemies) {
    int w, h;
    static int menuSelection = 0;
    static bool upPressed = false;
    static bool downPressed = false;
    static bool enterPressed = false;
    static TTF_Font* font = nullptr;
    SDL_Color white = { 255, 255, 255, 255 };

    const bool* keys = SDL_GetKeyboardState(NULL);

    switch (screen) {
    case MENU: {
        if (!font) {
            font = TTF_OpenFont("assets/arialmt.ttf", 32);
            if (!font) {
                SDL_Log("Erreur chargement police: %s", SDL_GetError());
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 50, 255);
        SDL_RenderClear(renderer);
        SDL_GetWindowSize(window, &w, &h);
		TitleMenu(renderer, w, h, white, "SHOOT'EM UP", font, w / 2 - 200, 200, 400, 80);

		ButtonMenu(renderer, w, h, white, "PLAY", font, w / 2 - 100, h / 2 - 60, 200, 50, menuSelection, 0);

        ButtonMenu(renderer, w, h, white, "QUIT", font, w / 2 - 100, h / 2 + 20, 200, 50, menuSelection, 1);
        
        if (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W]) {
            if (!upPressed) {
                menuSelection = (menuSelection - 1 + 2) % 2;
                upPressed = true;
            }
        }
        else upPressed = false;

        if (keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S]) {
            if (!downPressed) {
                menuSelection = (menuSelection - 1 + 2) % 2;
                downPressed = true;
            }
        }
        else downPressed = false;

        if (keys[SDL_SCANCODE_RETURN]) {
            if (!enterPressed) {
                enterPressed = true;
                if (menuSelection == 0) return LEVEL1;
                if (menuSelection == 1) return QUIT;
            }
        }
        else enterPressed = false;
		SDL_RenderPresent(renderer);
        break;
    }

    case LEVEL1: {
        if (player.HP <= 0) {
            screen = GAMEOVER;
            break;
        }

        static float spawnTimer = 0;
        const float spawnInterval = 1.5;

        player.handleInput(keys, dt);
        SDL_GetWindowSize(window, &w, &h);
        player.clampToScreen(w, h);
        player.updateBullets(dt);

        spawnTimer += dt;
        if (spawnTimer >= spawnInterval) {
            Enemy::spawnEnemy(enemies, w, h);
            spawnTimer = 0;
        }

        Enemy::updateEnemy(enemies);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, background, NULL, NULL);

        player.render(renderer);
        player.renderBullets(renderer);
        Enemy::renderEnemy(renderer, enemies);
        player.DisplayHP(renderer, player.HP);

        timeSinceLastHit += dt;
        if (timeSinceLastHit < collisionCooldown){
            
        }
        else {
            timeSinceLastHit = 0;
            player.Collide(enemies);
        }

        SDL_RenderPresent(renderer);

        if (keys[SDL_SCANCODE_ESCAPE]) {
            player.HP = 3;
            player.bullets.clear();
            enemies.clear();
            player.rect.x = 400.0f;
            player.rect.y = 300.0f;
            return MENU;
        }
        break;
    }
    case GAMEOVER:
        if (!font) {
            font = TTF_OpenFont("assets/arialmt.ttf", 32);
            if (!font) {
                SDL_Log("Erreur chargement police: %s", SDL_GetError());
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 50, 255);
        SDL_RenderClear(renderer);
        SDL_GetWindowSize(window, &w, &h);
        TitleMenu(renderer, w, h, white, "GAME OVER", font, w / 2 - 200, 200, 400, 80);

        ButtonMenu(renderer, w, h, white, "QUIT", font, w / 2 - 100, h / 2 + 20, 200, 50, menuSelection, 1);
 
        if (keys[SDL_SCANCODE_RETURN]) {
            if (!enterPressed) {
                enterPressed = true;
                if (menuSelection == 0) return LEVEL1;
                if (menuSelection == 1) return QUIT;
            }
        }
        else enterPressed = false;
        SDL_RenderPresent(renderer);
        break;

    case QUIT:
        break;
    }

    return screen;
}