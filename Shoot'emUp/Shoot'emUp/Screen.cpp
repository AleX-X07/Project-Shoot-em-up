// Load file
#include "Screen.h"

// Function for navigate in menu
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
                screen = LEVEL;
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

// Function for the game state
GameState updateGameState(GameState screen, SDL_Renderer* renderer, LoadRessource& MyRessource, Hero& player, float dt, SDL_Window* window, std::vector<Enemy>& enemies, std::vector<Bullet>& bullets, bool& restart, Level& MyLevel, FileManager& Level, std::vector<Item>& item) {
    // Variable static
    static int w, h;
    SDL_GetWindowSize(window, &w, &h);
    static int menuSelection = 0;
    static int menuDeathSelection = 0;
    static bool upPressed = false;
    static bool downPressed = false;
    static bool enterPressed = false;
    static bool escPressed = false;
    static int currentLevel = 0;
    static TTF_Font* font = nullptr;
    SDL_Color white = { 255, 255, 255, 255 };

    // Check the input
    const bool* keys = SDL_GetKeyboardState(NULL);

    switch (screen) {
    // If screen is MENU
    case MENU: {
        // Load font
        if (!font) {
            font = TTF_OpenFont("assets/arialmt.ttf", 32);
            if (!font) {
                SDL_Log("Erreur chargement police: %s", SDL_GetError());
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, MyRessource.backgroundHome, NULL, NULL);

        Texte(renderer, w, h, white, "SHOOT'EM UP", font, w / 2 - 200, 200, 400, 80);

        Button(renderer, w, h, white, "PLAY", font, w / 2 - 100, h / 2 - 60, 200, 50, menuSelection, 0);

        Button(renderer, w, h, white, "QUIT", font, w / 2 - 100, h / 2 + 20, 200, 50, menuSelection, 1);

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
                if (menuSelection == 0) {
                    return LEVEL;
                }
                if (menuSelection == 1) {
                    return QUIT;
                }
            }
        }
        else enterPressed = false;
        // Display MENU
        SDL_RenderPresent(renderer);
        break;
    }
    // If screen is LEVEL
    case LEVEL: {
        //Chek if player alive
        if (player.HP <= 0) {
            screen = GAMEOVER;
            break;
        }

        Level.readOrderLevel();

        // Check what level I'm in
        if (currentLevel != MyLevel.numLevel) {
            if (MyLevel.numLevel == 1) {
                Level = FileManager(Level.level_1);
                Level.readIntLevel(MyLevel.nbr_enemy, MyLevel.nbr_shooter, MyLevel.nbr_shooter_V2, MyLevel.nbr_boss);
                MyLevel.setMyLevel(MyLevel.nbr_enemy, MyLevel.nbr_shooter, MyLevel.nbr_shooter_V2, MyLevel.nbr_boss);
            }
            else if (MyLevel.numLevel == 2) {
                Level = FileManager(Level.level_2);
                Level.readIntLevel(MyLevel.nbr_enemy, MyLevel.nbr_shooter, MyLevel.nbr_shooter_V2, MyLevel.nbr_boss);
                MyLevel.setMyLevel(MyLevel.nbr_enemy, MyLevel.nbr_shooter, MyLevel.nbr_shooter_V2, MyLevel.nbr_boss);
            }
            currentLevel = MyLevel.numLevel;
        }

        MyLevel.displayLevel(renderer, MyRessource, player, dt, window, enemies, bullets, MyLevel, keys, w, h, item);

        // Win condition
        if (MyLevel.typeLevel(player) == 1) {
            MyLevel.reset(player, enemies);
            player.nbr_enemy_death = 0;  
            player.bossDeath = 0;        
            MyLevel.numLevel++;

            if (MyLevel.numLevel > 2) {
                return VICTORY;
            }
        }
        
        // Escape for BREAK
        if (keys[SDL_SCANCODE_ESCAPE]) {
            if (!escPressed) {
                escPressed = true;
                return PAUSE;
            }
        }
        else {
            escPressed = false;
        }
        break;
    }
    // If screen is PAUSE
    case PAUSE: {

        // Only render, not update
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, MyRessource.backgroundLevel1, NULL, NULL);

        player.render(renderer);
        player.renderBullets(renderer, player.heroBullets);
        Enemy::renderEnemy(renderer, enemies);
        player.HUD(renderer, MyRessource.heart, player.HP, player.score);

        // Background black transparent
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_RenderFillRect(renderer, NULL);

        Texte(renderer, w, h, white, "PAUSE", font, w / 2 - 200, 200, 400, 100);
        SDL_RenderPresent(renderer);

        if (keys[SDL_SCANCODE_ESCAPE]) {
            if (!escPressed) {
                escPressed = true;
                return LEVEL;
            }
        }
        else {
            escPressed = false;
        }
        break;
    }
    // If screen is GAMEOVER
    case GAMEOVER:

        // Load font
        if (!font) {
            font = TTF_OpenFont("assets/arialmt.ttf", 32);
            if (!font) {
                SDL_Log("Erreur chargement police: %s", SDL_GetError());
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 50, 255);
        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, MyRessource.backgroundHome, NULL, NULL);
        SDL_GetWindowSize(window, &w, &h);

        Texte(renderer, w, h, white, "GAME OVER", font, w / 2 - 200, 200, 400, 80);

        Button(renderer, w, h, white, "MENU", font, w / 2 - 100, h / 2 - 60, 200, 50, menuDeathSelection, 0);

        Button(renderer, w, h, white, "QUIT", font, w / 2 - 100, h / 2 + 20, 200, 50, menuDeathSelection, 1);

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
        // Display PAUSE
        SDL_RenderPresent(renderer);
        break;
    // If screen is VICTORY
    case VICTORY:

            SDL_SetRenderDrawColor(renderer, 0, 0, 50, 255);
            SDL_RenderClear(renderer);
            SDL_RenderTexture(renderer, MyRessource.backgroundHome, NULL, NULL);
            SDL_GetWindowSize(window, &w, &h);

            Texte(renderer, w, h, white, "VICTORY", font, w / 2 - 200, 200, 400, 80);

            Button(renderer, w, h, white, "MENU", font, w / 2 - 100, h / 2 - 60, 200, 50, menuDeathSelection, 0);

            Button(renderer, w, h, white, "QUIT", font, w / 2 - 100, h / 2 + 20, 200, 50, menuDeathSelection, 1);

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
                        currentLevel = 0;
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
            // Display VICTORY
            SDL_RenderPresent(renderer);
            break;
    // If screen is QUIT
    case QUIT:
        // Close game
        break;
    }
    // Return the game state
    return screen;
}