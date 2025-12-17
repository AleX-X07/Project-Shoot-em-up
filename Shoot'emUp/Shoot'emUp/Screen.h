#pragma once

#include <vector>
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "Hero.h"
#include "Enemy.h"
#include "Menu.h"
#include "LoadRessource.h"

void NavigateMenu(GameState screen, SDL_Event event, int menuSelection, bool enterPressed);
GameState updateGameState(GameState screen, SDL_Renderer* renderer, SDL_Texture* background, Entity& player, float dt, SDL_Window* window, std::vector<Enemy>& enemies, std::vector<Bullet>& bullets, SDL_Texture* enemyTexture, SDL_Texture* heart, bool& restart, Menu& menu, LoadRessource Ressources, TTF_Font* font);

