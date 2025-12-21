#include "Screen.h"

float collisionCooldown = 0.5f;
float collisionCooldownEnemy = 0.2f;
float timeSinceLastHit = 0.0f;
float timeSinceLastHitBullet = 0.0f;

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

GameState updateGameState(GameState screen, SDL_Renderer* renderer, LoadRessource& MyRessource, Entity& player, float dt, SDL_Window* window, std::vector<Enemy>& enemies, std::vector<Bullet>& bullets, bool& restart, Level& MyLevel1) {
    static int w, h;
    static int menuSelection = 0;
    static int menuDeathSelection = 0;
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

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, MyRessource.backgroundHome, NULL, NULL);

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
        player.updateBullets(dt, player.heroBullets);

        spawnTimer += dt; // Spawn enemies
        if (spawnTimer >= spawnInterval) {
            Enemy::EnemyManager(enemies, renderer, w, h, MyRessource, MyLevel1);
            spawnTimer = 0;
        }

        Enemy::updateEnemy(enemies, dt, w, h);

        for (auto& e : enemies) { // Shoot for enemies
            if (e.numEnemy == 2) {
                e.shoot(e.enemiesBullet);
            }
            else if (e.numEnemy == 3) {
                e.shootV2(e.enemiesBullet);
            }
            else if (e.numEnemy == 10) {
                e.shootBoss(e.enemiesBullet);
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, MyRessource.backgroundLevel1, NULL, NULL);

        player.render(renderer);
        player.renderBullets(renderer, player.heroBullets);
        Enemy::renderEnemy(renderer, enemies);
        player.HUD(renderer, MyRessource.heart, player.HP, player.Score);

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

        timeSinceLastHitBullet += dt;
        if (timeSinceLastHitBullet >= collisionCooldownEnemy) {
            for (auto& e : enemies) {
                for (int i = e.enemiesBullet.size() - 1; i >= 0; i--) {
                    SDL_FRect bulletRect = { e.enemiesBullet[i].x, e.enemiesBullet[i].y,
                                             e.enemiesBullet[i].w, e.enemiesBullet[i].h };
                    if (SDL_HasRectIntersectionFloat(&player.rect, &bulletRect)) {
                        player.HP--;
                        e.enemiesBullet.erase(e.enemiesBullet.begin() + i);
                        timeSinceLastHitBullet = 0;
                        break;
                    }
                }
            }
        }

        player.CollideBullet(enemies);

        SDL_RenderPresent(renderer);

        if (keys[SDL_SCANCODE_ESCAPE]) {
            player.HP = 4;
            player.heroBullets.clear();
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

        ButtonMenu(renderer, w, h, white, "MENU", font, w / 2 - 100, h / 2 - 60, 200, 50, menuDeathSelection, 0);

        ButtonMenu(renderer, w, h, white, "QUIT", font, w / 2 - 100, h / 2 + 20, 200, 50, menuDeathSelection, 1);

        if (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W]) {
            if (!upPressed) {
                menuDeathSelection = (menuDeathSelection - 1 + 2) % 2;
                upPressed = true;
            }
        }
        else {
            upPressed = false;
        }
        if (keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S]) {
            if (!downPressed) {
                menuDeathSelection = (menuDeathSelection - 1 + 2) % 2;
                downPressed = true;
            }
        }
        else {
            downPressed = false;
        }
        if (keys[SDL_SCANCODE_RETURN]) {
            if (!enterPressed) {
                enterPressed = true;
                if (menuDeathSelection == 0) {
                    restart = true;
                    return MENU;
                }
                if (menuDeathSelection == 1) {
                    return QUIT;
                }
            }
        }
        else {
            enterPressed = false;
        }
        SDL_RenderPresent(renderer);
        break;
    case QUIT:
        break;
    }
    return screen;
}