#pragma once
#include <SDL3/SDL.h>
#include "Hero.h"
#include "Enemy.h"

enum GameState {
    MENU,
    LEVEL1,
    LEVEL2,
    GAMEOVER,
    QUIT
};

void NavigateMenu(GameState screen, SDL_Event event, int menuSelection, bool enterPressed);
GameState updateGameState(GameState screen, SDL_Renderer* renderer, SDL_Texture* background, Entity& player, float dt, SDL_Window* window, std::vector<Enemy>& enemies, std::vector<Bullet>& bullets, SDL_Texture* enemyTexture, SDL_Texture* heart, bool& restart);

