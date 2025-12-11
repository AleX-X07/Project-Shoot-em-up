#pragma once
#include <SDL3/SDL.h>
#include "Hero.h"
#include "EnemyManager.h"

enum GameState {
    MENU,
    LEVEL1,
    LEVEL2,
    GAMEOVER,
    QUIT
};

GameState updateGameState(GameState screen, SDL_Renderer* renderer, SDL_Texture* background, Entity& player, float dt, SDL_Window* window, EnemyManager* enemyManager);
void NavigateMenu(GameState screen, SDL_Event event, bool keepgoing);