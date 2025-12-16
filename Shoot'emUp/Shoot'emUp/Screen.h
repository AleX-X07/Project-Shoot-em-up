#pragma once
#include <SDL3/SDL.h>
#include "Hero.h"
#include "Enemy.h"
#include "Enemy_Manager.h"

enum GameState {
    MENU,
    LEVEL1,
    LEVEL2,
    GAMEOVER,
    QUIT
};

GameState updateGameState(GameState screen, SDL_Renderer* renderer, SDL_Texture* background, Entity& player, float dt,
    SDL_Window* window/*, std::vector<Enemy>& enemies, std::vector<Shooter_Enemy>& Shooter, Uint32 now*/);
