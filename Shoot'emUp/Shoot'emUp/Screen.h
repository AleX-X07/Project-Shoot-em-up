#pragma once
#include "Hero.h"
#include "Enemy.h"
#include "Menu.h"
#include "Bullet.h"
#include "LoadRessource.h"
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include "Enemy_Manager.h"

enum GameState {
    MENU,
    LEVEL1,
    LEVEL2,
    GAMEOVER,
    QUIT
};

void NavigateMenu(GameState screen, SDL_Event event, int menuSelection, bool enterPressed);
GameState updateGameState(GameState screen, SDL_Renderer* renderer, LoadRessource& MyRessource, Entity& player, float dt, SDL_Window* window, std::vector<Enemy>& enemies, std::vector<Bullet>& bullets,bool& restart);