#include "Screen.h"


float collisionCooldown = 0.5f;
float timeSinceLastHit = 0.0f;

TTF_Font* font = nullptr;

void NavigateMenu(GameState screen, SDL_Event event, int menuSelection, bool enterPressed) {
    enterPressed = false;
    menuSelection = 0;
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

GameState updateGameState(GameState screen, SDL_Renderer* renderer, SDL_Texture* background, Entity& player, float dt, SDL_Window* window, std::vector<Enemy>& enemies, std::vector<Bullet>& bullets, SDL_Texture* enemyTexture, SDL_Texture* heart, bool& restart, Menu& menu, LoadRessource Ressources) {
    
    font = TTF_OpenFont("assets/arialmt.ttf", 32);
    if (!font) {
        SDL_Log("Erreur chargement police: %s", SDL_GetError());
    }
    int w, h;
    static int menuDeathSelection = 0;

    static bool upPressedGameOver = false;
    static bool downPressedGameOver = false;
    static bool enterPressedGameOver = false;

    SDL_Color white = { 255, 255, 255, 255 };

    const bool* keys = SDL_GetKeyboardState(NULL);

    switch (screen) {
    case MENU: {
        screen = menu.DisplayMenu(renderer, window, font, Ressources);
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
            Enemy::spawnEnemy(enemies, w, h, renderer, enemyTexture);
            spawnTimer = 0;
        }

        Enemy::updateEnemy(enemies);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, background, NULL, NULL);

        player.render(renderer);
        player.renderBullets(renderer);
        Enemy::renderEnemy(renderer, enemies);
        player.HUD(renderer, heart, player.HP, player.Score);

        timeSinceLastHit += dt;
        if (timeSinceLastHit >= collisionCooldown) {
            timeSinceLastHit = 0;

            for (auto& e : enemies) {
                if (SDL_HasRectIntersectionFloat(&player.rect, &e.rect)) {
                    player.HP--;
                    break;
                }
            }
        }

        player.Collide(enemies);

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
        //Menu::TitleMenu(renderer, w, h, white, "GAME OVER", font, w / 2 - 200, 200, 400, 80);

        //Menu::ButtonMenu(renderer, w, h, white, "MENU", font, w / 2 - 100, h / 2 - 60, 200, 50, menuDeathSelection, 0, Ressources);

        //Menu::ButtonMenu(renderer, w, h, white, "QUIT", font, w / 2 - 100, h / 2 + 20, 200, 50, menuDeathSelection, 1, Ressources);
 
        if (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W]) {
            if (!upPressedGameOver) {
                menuDeathSelection = (menuDeathSelection - 1 + 2) % 2;
                upPressedGameOver = true;
            }
        }
        else upPressedGameOver = false;

        if (keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S]) {
            if (!downPressedGameOver) {
                menuDeathSelection = (menuDeathSelection - 1 + 2) % 2;
                downPressedGameOver = true;
            }
        }
        else downPressedGameOver = false;

        if (keys[SDL_SCANCODE_RETURN]) {
            if (!enterPressedGameOver) {
                enterPressedGameOver = true;
                if (menuDeathSelection == 0) {
                    restart = true;
                    return MENU;
                }
                if (menuDeathSelection == 1) return QUIT;
            }
        }
        else enterPressedGameOver = false;
        SDL_RenderPresent(renderer);
        break;
    case QUIT:
        break;
    }

    return screen;
}