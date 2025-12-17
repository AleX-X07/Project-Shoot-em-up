#include "Screen.h"
#include "Menu.h"
#include "Enemy.h"
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include "Enemy_Manager.h"
#include "Shooter_Enemy.h"

GameState updateGameState(GameState screen, SDL_Renderer* renderer, SDL_Texture* background, Entity& player, float dt, SDL_Window* window) {
    int w, h;
    static int menuSelection = 0;
    static bool upPressed = false;
    static bool downPressed = false;
    static bool enterPressed = false;
    static TTF_Font* font = nullptr;
    static EnemyManager EM;
    static Shooter_Enemy SE;

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
        SDL_Color white = { 255, 255, 255, 255 };
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

        // Input et mise à jour du joueur
        player.handleInput(keys, dt);
        SDL_GetWindowSize(window, &w, &h);
        player.clampToScreen(w, h);
        player.updateBullets(dt);

        // Mise à jour des ennemis
        int windowWidth;
        int windowHeight;
        Uint32 now = SDL_GetTicks();
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);

        EM.spawn(windowWidth, windowHeight, now);
        EM.update(windowWidth, now);
        EM.cleanBullet();

<<<<<<< HEAD
        // Effacer l'écran
=======
        SE.spawnShooter_Enemy(Shooter, windowWidth, windowHeight);
        SE.updateShooter_Enemy(Shooter);
        //Enemy::updateEnemy(enemies);
        //Shooter_Enemy::updateShooter_Enemy(Shooter);

>>>>>>> 6b492029b84388f2ee313662d4a7c317ac7d449f
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Fond
        SDL_RenderTexture(renderer, background, NULL, NULL);

        // Ennemis (en arrière-plan)
        EM.render(renderer);

        // Joueur et ses bullets (au premier plan)
        player.render(renderer);
        player.renderBullets(renderer);
        player.DisplayHP(renderer, player.HP);

        // Présenter tout à l'écran
        SDL_RenderPresent(renderer);

        // Retour au menu
        if (keys[SDL_SCANCODE_ESCAPE]) {
            player.HP = 3;
            player.bullets.clear();

            // Nettoyage des enemies
            EM.enemies.clear();
            EM.Shooter.clear();
            EM.bullets.clear();

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